/**
 * File:   font_loader_custom.c
 * Author: AWTK Develop Team
 * Brief:  custom font loader
 *
 * Copyright (c) 2020 - 2020  Guangzhou ZHIYUAN Electronics Co.,Ltd.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * License file for more details.
 *
 */

/**
 * History:
 * ================================================================
 * 2020-08-08 Li XianJing <xianjimli@hotmail.com> created
 *
 */

#include "tkc/mem.h"
#include "tkc/utils.h"
#include "base/glyph_cache.h"
#include "tkc/data_reader_factory.h"

#include "font_loader_custom.h"

typedef struct _font_bitmap_custom_t {
  font_t base;

  char* url;
  glyph_cache_t cache;
  data_reader_t* reader;
  font_bitmap_header_t header;

  uint32_t index_nr;
  font_bitmap_index_t* index;

} font_bitmap_custom_t;

static ret_t destroy_glyph(void* data) {
  glyph_t* g = (glyph_t*)data;
  if (g->data != NULL) {
    TKMEM_FREE(g->data);
  }
  glyph_destroy(g);

  return RET_OK;
}

static font_bitmap_index_t* find_glyph(font_bitmap_index_t* elms, uint32_t nr, wchar_t c) {
  int low = 0;
  int mid = 0;
  int result = 0;
  int high = nr - 1;

  while (low <= high) {
    mid = low + ((high - low) >> 1);
    result = elms[mid].c - c;

    if (result == 0) {
      return elms + mid;
    } else if (result < 0) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return NULL;
}

static glyph_t* font_bitmap_custom_load_glyph(font_t* f, wchar_t c) {
  int ret = 0;
  int size = 0;
  int offset = 0;
  void* data = NULL;
  glyph_t* g = NULL;
  font_bitmap_custom_t* font = (font_bitmap_custom_t*)f;
  font_bitmap_index_t* index = find_glyph(font->index, font->index_nr, c);
  return_value_if_fail(index != NULL, NULL);

  g = TKMEM_ZALLOC(glyph_t);
  return_value_if_fail(g != NULL, NULL);

  size = sizeof(*g);
  memset(g, 0x00, size);
  ret = data_reader_read(font->reader, index->offset, g, size);
  ENSURE(ret == size);

  if (c != ' ') {
    size = g->w * g->h;
    data = TKMEM_ALLOC(size);

    if (data != NULL) {
      offset = index->offset + sizeof(glyph_t) - sizeof(g->data);
      ret = data_reader_read(font->reader, offset, data, size);
      ENSURE(ret == size);
      g->data = data;
    } else {
      TKMEM_FREE(g);
    }
  } else {
    g->data = NULL;
  }

  return g;
}

static ret_t font_bitmap_custom_get_glyph(font_t* f, wchar_t c, font_size_t font_size, glyph_t* g) {
  glyph_t* gg = NULL;
  font_bitmap_custom_t* font = (font_bitmap_custom_t*)f;

  font_size = font->header.font_size;
  if (glyph_cache_lookup(&(font->cache), c, font_size, g) == RET_OK) {
    return RET_OK;
  }

  gg = font_bitmap_custom_load_glyph(f, c);
  if (gg != NULL) {
    if (glyph_cache_add(&(font->cache), c, font_size, gg) != RET_OK) {
      destroy_glyph(gg);
      return RET_NOT_FOUND;
    }
  } else {
    return RET_NOT_FOUND;
  }

  return glyph_cache_lookup(&(font->cache), c, font_size, g);
}

static bool_t font_bitmap_custom_match(font_t* f, const char* name, font_size_t font_size) {
  font_bitmap_custom_t* font = (font_bitmap_custom_t*)f;

  if (name == NULL || strcmp(name, font->base.name) == 0) {
    return TRUE;
  }

  return FALSE;
}

static ret_t font_bitmap_custom_destroy(font_t* f) {
  font_bitmap_custom_t* font = (font_bitmap_custom_t*)f;

  TKMEM_FREE(font->url);
  TKMEM_FREE(font->index);
  glyph_cache_deinit(&(font->cache));
  data_reader_destroy(font->reader);
  memset(font, 0x00, sizeof(*font));

  TKMEM_FREE(f);
  return RET_OK;
}

static font_vmetrics_t font_bitmap_custom_get_vmetrics(font_t* f, font_size_t font_size) {
  font_vmetrics_t vmetrics;
  font_bitmap_custom_t* font = (font_bitmap_custom_t*)f;
  font_bitmap_header_t* header = &(font->header);

  vmetrics.ascent = header->ascent;
  vmetrics.descent = header->descent;
  vmetrics.line_gap = header->line_gap;

  return vmetrics;
}

static ret_t font_bitmap_custom_shrink_cache(font_t* f, uint32_t cache_nr) {
  font_bitmap_custom_t* font = (font_bitmap_custom_t*)f;

  return glyph_cache_shrink(&(font->cache), cache_nr);
}

font_t* font_bitmap_init(font_bitmap_custom_t* f, const char* name) {
  int ret = 0;
  int index_size = 0;
  int header_size = 0;
  return_value_if_fail(f != NULL, NULL);

  f->base.match = font_bitmap_custom_match;
  f->base.get_glyph = font_bitmap_custom_get_glyph;
  f->base.get_vmetrics = font_bitmap_custom_get_vmetrics;
  f->base.shrink_cache = font_bitmap_custom_shrink_cache;
  f->base.destroy = font_bitmap_custom_destroy;
  f->base.desc = "custom bitmap font";
  tk_strncpy(f->base.name, name, TK_NAME_LEN);

  glyph_cache_init(&(f->cache), TK_GLYPH_CACHE_NR, destroy_glyph);

  header_size = sizeof(f->header) - sizeof(f->header.index);
  ret = data_reader_read(f->reader, 0, &(f->header), header_size);
  ENSURE(ret == header_size);

  f->index_nr = f->header.char_nr;
  ENSURE(f->index_nr > 0);

  index_size = f->index_nr * sizeof(font_bitmap_index_t);
  f->index = TKMEM_ALLOC(index_size);
  ENSURE(f->index != NULL);

  ret = data_reader_read(f->reader, header_size, f->index, index_size);
  ENSURE(ret == index_size);

  return &(f->base);
}

font_t* font_bitmap_custom_create(const char* name, const uint8_t* buff, uint32_t buff_size) {
  font_bitmap_custom_t* font = NULL;
  return_value_if_fail(buff != NULL && name != NULL && buff_size > 0, NULL);

  font = TKMEM_ZALLOC(font_bitmap_custom_t);
  return_value_if_fail(font != NULL, NULL);

  font->url = tk_strndup((const char*)buff, buff_size);
  ENSURE(font->url != NULL);
  font->reader = data_reader_factory_create_reader(data_reader_factory(), font->url);
  ENSURE(font->reader != NULL);

  return font_bitmap_init(font, name);
}

static font_t* font_loader_custom_load(font_loader_t* loader, const char* name, const uint8_t* buff,
                                       uint32_t buff_size) {
  return font_bitmap_custom_create(name, buff, buff_size);
}

font_loader_t* font_loader_custom(void) {
  static font_loader_t loader;
  loader.type = ASSET_TYPE_FONT_BMP;
  loader.load = font_loader_custom_load;

  return &loader;
}
