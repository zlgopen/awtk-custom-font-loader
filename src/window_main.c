/**
 * File:   window_main.c
 * Author: AWTK Develop Team
 * Brief:  window main
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

#include "awtk.h"
#include "../res/assets.inc"
#include "tkc/data_reader_file.h"
#include "tkc/data_reader_factory.h"
#include "common/font_loader_custom.h"

static ret_t label_set_font_size(widget_t* widget, int font_size) {
#ifndef WITH_NANOVG_GPU
  char font[32];
  tk_snprintf(font, sizeof(font), "font_%d", font_size);
  widget_set_style_str(widget, "font_name", font);
#else
  widget_set_style_int(widget, "font_size", font_size);
#endif
}

static void window_main_create(void) {
  widget_t* win = window_create(NULL, 0, 0, 0, 0);
  widget_t* title = label_create(win, 10, 10, 200, 30);
  widget_t* content = label_create(win, 10, 50, 200, 30);

  label_set_font_size(title, 20);
  label_set_font_size(content, 18);

  widget_set_text_utf8(title, "This is Title");
  widget_set_text_utf8(content, "this is content");

  widget_layout(win);
}

static ret_t add_custom_font(const char* font_name, const char* url) {
  asset_info_t* info =
      asset_info_create(ASSET_TYPE_FONT, ASSET_TYPE_FONT_BMP, font_name, strlen(url) + 1);
  return_value_if_fail(info != NULL, RET_FAIL);

  strcpy((char*)(info->data), url);

  return assets_manager_add(assets_manager(), info);
}

static ret_t application_init_fonts(void) {
#ifndef WITH_NANOVG_GPU
  add_custom_font("font_18", "file://./data/font_18.bin");
  add_custom_font("font_20", "file://./data/font_20.bin");
  font_manager()->loader = font_loader_custom();
  system_info_set_default_font(system_info(), "font18");
#endif /*WITH_NANOVG_GPU*/

  return RET_OK;
}

ret_t application_init() {
  application_init_fonts();

  window_main_create();

  return RET_OK;
}

ret_t application_exit() {
  log_debug("application_exit\n");
  return RET_OK;
}

#include "awtk_main.inc"
