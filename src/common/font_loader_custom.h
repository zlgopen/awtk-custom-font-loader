/**
 * File:   font_loader_custom.h
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

#ifndef TK_FONT_LOADER_CUSTOM_H
#define TK_FONT_LOADER_CUSTOM_H

#include "base/font_loader.h"
#include "font_loader/font_loader_bitmap.h"

BEGIN_C_DECLS

/**
 * @class font_loader_custom_t
 * @parent font_loader_t
 * 自定义的字体加载器的例子(可以根据自己的情况进行改造和完善)。
 * @annotation["fake"]
 *
 */

/**
 * @method font_loader_custom
 * @annotation ["constructor"]
 *
 * 获取自定义bitmap字体加载器对象。
 *
 * @return {font_loader_t*} 返回字体加载器对象。
 */
font_loader_t* font_loader_custom(void);

END_C_DECLS

#endif /*TK_FONT_LOADER_CUSTOM_H*/
