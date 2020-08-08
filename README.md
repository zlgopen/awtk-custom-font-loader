# awtk-custom-font-loader

自定义的字体加载器的例子（可以根据自己的情况进行改造和完善）。

在有平台上，内部 flash 很小，不足以存放字体资源。放在文件系统里，又没有足够的内存来加载整个字体文件。此时需要自定义字体加载器，以便只加载当前需要的部分字体。这里提供了一个自定义的字体加载器的例子（可以根据自己的情况进行改造和完善）。

在这个例子中，采用了与 AWTK 中位图字体同样的数据格式，字体数据放在外部文件中，只是加载索引到内存，可以大大减少内存的需求。如果你的平台连加载完整索引的内存都没有，那需要自己改造一下，使用稀疏索引的方式。

## 准备

1. 获取 awtk 并编译

```
git clone https://github.com/zlgopen/awtk.git
cd awtk; scons; cd -
```

2. 获取 awtk-custom-font-loader 并编译
```
git clone https://github.com/zlgopen/awtk-custom-font-loader.git
cd awtk-custom-font-loader; scons
```

## 生成字体数据

放在文件系统中的字体数据可以用 AWTK 提供的 fontgen 生成。如：

```
../awtk/bin/fontgen design/default/fonts/default.ttf design/default/fonts/text.txt data/font_20.bin 20
```

## 运行

> 考虑到 github 的下载速度，生成的临时资源没放到 git 中，需要自己生成资源：

```
./scripts/update_res.py all
```

```
./bin/demo
```

> 本文以 Linux/MacOS 为例，Windows 可能会微妙差异，请酌情处理。

## 说明

* 1. 为了避免 assets\_manager 把整个资源读取到内存，这里需要手工构建 asset 对象，放到 assets\_manager 里。

```c
static ret_t add_custom_font(const char* font_name, const char* filename) {
  asset_info_t* info = asset_info_create(ASSET_TYPE_FONT, ASSET_TYPE_FONT_BMP, 
      font_name, strlen(filename) + 1);
  return_value_if_fail(info != NULL, RET_FAIL);

  strcpy((char*)(info->data), filename);

  return assets_manager_add(assets_manager(), info);
}
```

> 请参考 window_main.c

* 2. OpenGL 版本不支持自定义字体。

```c
static ret_t application_init_fonts(void) {
#ifndef WITH_NANOVG_GPU
  add_custom_font("font_18", "file://./data/font_18.bin");
  add_custom_font("font_20", "file://./data/font_20.bin");
  font_manager()->loader = font_loader_custom();
  system_info_set_default_font(system_info(), "font_18");
#endif /*WITH_NANOVG_GPU*/

  return RET_OK;
}
```

> 请参考 window_main.c

* 3. 如果不想使用文件系统，而是直接读取 flash，可以实现 data\_reader\_t 接口，并注册到 data_reader_factory 中。

如：

```c
data_reader_factory_register(data_reader_factory(), "flash", data_reader_flash_create);
```