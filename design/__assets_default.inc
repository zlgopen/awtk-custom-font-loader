#include "awtk.h"
#include "base/assets_manager.h"
#ifndef WITH_FS_RES
#include "default/inc/strings/ko_KR.data"
#include "default/inc/strings/zh_CN.data"
#include "default/inc/strings/zh_TW.data"
#include "default/inc/strings/en_US.data"
#include "default/inc/styles/main.data"
#include "default/inc/styles/keyboard.data"
#include "default/inc/styles/default.data"
#include "default/inc/styles/window1.data"
#include "default/inc/ui/kb_ascii.data"
#include "default/inc/ui/kb_phone.data"
#include "default/inc/ui/main.data"
#include "default/inc/ui/kb_int.data"
#include "default/inc/ui/kb_hex.data"
#include "default/inc/ui/settings.data"
#include "default/inc/ui/kb_float.data"
#include "default/inc/ui/window1.data"
#include "default/inc/ui/kb_ufloat.data"
#include "default/inc/ui/kb_default.data"
#include "default/inc/ui/kb_uint.data"
#include "default/inc/data/com_zlg_app_json.data"
#include "default/inc/data/gpinyin_dat.data"
#include "default/inc/data/test_dat.data"
#include "default/inc/data/suggest_words_zh_cn_dat.data"
#include "default/inc/data/test_json.data"
#include "default/inc/data/a_b_c_any.data"
#include "default/inc/data/awtk_db.data"
#ifdef WITH_STB_IMAGE
#include "default/inc/images/checked.res"
#include "default/inc/images/shift.res"
#include "default/inc/images/earth.res"
#include "default/inc/images/dialog_title.res"
#include "default/inc/images/arrow_up_n.res"
#include "default/inc/images/cursor_hand.res"
#include "default/inc/images/arrow_right_p.res"
#include "default/inc/images/empty.res"
#include "default/inc/images/edit_clear_p.res"
#include "default/inc/images/arrow_up_o.res"
#include "default/inc/images/arrow_left_o.res"
#include "default/inc/images/en.res"
#include "default/inc/images/arrow_left_n.res"
#include "default/inc/images/dns.res"
#include "default/inc/images/settings.res"
#include "default/inc/images/radio_checked.res"
#include "default/inc/images/dns_focused.res"
#include "default/inc/images/zh.res"
#include "default/inc/images/shifton.res"
#include "default/inc/images/check.res"
#include "default/inc/images/cursor.res"
#include "default/inc/images/eip.res"
#include "default/inc/images/arrow_down_n.res"
#include "default/inc/images/vpn.res"
#include "default/inc/images/arrow_down_o.res"
#include "default/inc/images/vpn_focused.res"
#include "default/inc/images/cursor_text.res"
#include "default/inc/images/unchecked.res"
#include "default/inc/images/arrow_down_p.res"
#include "default/inc/images/switch.res"
#include "default/inc/images/radio_unchecked.res"
#include "default/inc/images/eip_focused.res"
#include "default/inc/images/arrow_up_p.res"
#include "default/inc/images/edit_clear_o.res"
#include "default/inc/images/arrow_right_n.res"
#include "default/inc/images/arrow_right_o.res"
#include "default/inc/images/edit_clear_n.res"
#include "default/inc/images/settings_focused.res"
#include "default/inc/images/backspace.res"
#include "default/inc/images/arrow_left_p.res"
#else
#include "default/inc/images/arrow_right_o.data"
#include "default/inc/images/eip.data"
#include "default/inc/images/earth.data"
#include "default/inc/images/dns.data"
#include "default/inc/images/shift.data"
#include "default/inc/images/arrow_up_p.data"
#include "default/inc/images/dns_focused.data"
#include "default/inc/images/en.data"
#include "default/inc/images/arrow_right_n.data"
#include "default/inc/images/cursor.data"
#include "default/inc/images/switch.data"
#include "default/inc/images/checked.data"
#include "default/inc/images/zh.data"
#include "default/inc/images/arrow_right_p.data"
#include "default/inc/images/arrow_up_o.data"
#include "default/inc/images/empty.data"
#include "default/inc/images/radio_unchecked.data"
#include "default/inc/images/settings.data"
#include "default/inc/images/shifton.data"
#include "default/inc/images/arrow_up_n.data"
#include "default/inc/images/backspace.data"
#include "default/inc/images/arrow_left_p.data"
#include "default/inc/images/edit_clear_n.data"
#include "default/inc/images/dialog_title.data"
#include "default/inc/images/cursor_hand.data"
#include "default/inc/images/settings_focused.data"
#include "default/inc/images/arrow_down_p.data"
#include "default/inc/images/vpn.data"
#include "default/inc/images/edit_clear_o.data"
#include "default/inc/images/vpn_focused.data"
#include "default/inc/images/arrow_left_o.data"
#include "default/inc/images/check.data"
#include "default/inc/images/eip_focused.data"
#include "default/inc/images/arrow_down_o.data"
#include "default/inc/images/radio_checked.data"
#include "default/inc/images/unchecked.data"
#include "default/inc/images/arrow_down_n.data"
#include "default/inc/images/cursor_text.data"
#include "default/inc/images/arrow_left_n.data"
#include "default/inc/images/edit_clear_p.data"
#endif /*WITH_STB_IMAGE*/
#ifdef WITH_VGCANVAS
#endif /*WITH_VGCANVAS*/
#ifdef WITH_TRUETYPE_FONT
#include "default/inc/fonts/thin.res"
#include "default/inc/fonts/bold.res"
#include "default/inc/fonts/default.res"
#include "default/inc/fonts/ko_KR.res"
#include "default/inc/fonts/italic.res"
#include "default/inc/fonts/zh_TW.res"
#include "default/inc/fonts/mono.res"
#include "default/inc/fonts/default.mini.res"
#include "default/inc/fonts/light.res"
#include "default/inc/fonts/led.res"
#else /*WITH_TRUETYPE_FONT*/
#endif /*WITH_TRUETYPE_FONT*/
#endif /*WITH_FS_RES*/

ret_t assets_init_default(void) {
  assets_manager_t* am = assets_manager();

#ifdef WITH_FS_RES
  assets_manager_preload(am, ASSET_TYPE_FONT, "default");
  assets_manager_preload(am, ASSET_TYPE_STYLE, "default");
#else
  assets_manager_add(am, strings_ko_KR);
  assets_manager_add(am, strings_zh_CN);
  assets_manager_add(am, strings_zh_TW);
  assets_manager_add(am, strings_en_US);
  assets_manager_add(am, style_main);
  assets_manager_add(am, style_keyboard);
  assets_manager_add(am, style_default);
  assets_manager_add(am, style_window1);
  assets_manager_add(am, ui_kb_ascii);
  assets_manager_add(am, ui_kb_phone);
  assets_manager_add(am, ui_main);
  assets_manager_add(am, ui_kb_int);
  assets_manager_add(am, ui_kb_hex);
  assets_manager_add(am, ui_settings);
  assets_manager_add(am, ui_kb_float);
  assets_manager_add(am, ui_window1);
  assets_manager_add(am, ui_kb_ufloat);
  assets_manager_add(am, ui_kb_default);
  assets_manager_add(am, ui_kb_uint);
  assets_manager_add(am, data_com_zlg_app_json);
  assets_manager_add(am, data_gpinyin_dat);
  assets_manager_add(am, data_test_dat);
  assets_manager_add(am, data_suggest_words_zh_cn_dat);
  assets_manager_add(am, data_test_json);
  assets_manager_add(am, data_a_b_c_any);
  assets_manager_add(am, data_awtk_db);
  assets_manager_add(am, image_checked);
  assets_manager_add(am, image_shift);
  assets_manager_add(am, image_earth);
  assets_manager_add(am, image_dialog_title);
  assets_manager_add(am, image_arrow_up_n);
  assets_manager_add(am, image_cursor_hand);
  assets_manager_add(am, image_arrow_right_p);
  assets_manager_add(am, image_empty);
  assets_manager_add(am, image_edit_clear_p);
  assets_manager_add(am, image_arrow_up_o);
  assets_manager_add(am, image_arrow_left_o);
  assets_manager_add(am, image_en);
  assets_manager_add(am, image_arrow_left_n);
  assets_manager_add(am, image_dns);
  assets_manager_add(am, image_settings);
  assets_manager_add(am, image_radio_checked);
  assets_manager_add(am, image_dns_focused);
  assets_manager_add(am, image_zh);
  assets_manager_add(am, image_shifton);
  assets_manager_add(am, image_check);
  assets_manager_add(am, image_cursor);
  assets_manager_add(am, image_eip);
  assets_manager_add(am, image_arrow_down_n);
  assets_manager_add(am, image_vpn);
  assets_manager_add(am, image_arrow_down_o);
  assets_manager_add(am, image_vpn_focused);
  assets_manager_add(am, image_cursor_text);
  assets_manager_add(am, image_unchecked);
  assets_manager_add(am, image_arrow_down_p);
  assets_manager_add(am, image_switch);
  assets_manager_add(am, image_radio_unchecked);
  assets_manager_add(am, image_eip_focused);
  assets_manager_add(am, image_arrow_up_p);
  assets_manager_add(am, image_edit_clear_o);
  assets_manager_add(am, image_arrow_right_n);
  assets_manager_add(am, image_arrow_right_o);
  assets_manager_add(am, image_edit_clear_n);
  assets_manager_add(am, image_settings_focused);
  assets_manager_add(am, image_backspace);
  assets_manager_add(am, image_arrow_left_p);
#ifdef WITH_VGCANVAS
#endif /*WITH_VGCANVAS*/
#ifdef WITH_TRUETYPE_FONT
  assets_manager_add(am, font_thin);
  assets_manager_add(am, font_bold);
  assets_manager_add(am, font_default);
  assets_manager_add(am, font_ko_KR);
  assets_manager_add(am, font_italic);
  assets_manager_add(am, font_zh_TW);
  assets_manager_add(am, font_mono);
  assets_manager_add(am, font_default_mini);
  assets_manager_add(am, font_light);
  assets_manager_add(am, font_led);
#else /*WITH_TRUETYPE_FONT*/
#endif /*WITH_TRUETYPE_FONT*/
#endif

  tk_init_assets();
  return RET_OK;
}
