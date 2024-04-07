// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: muxdevice

#ifndef _MUXDEVICE_UI_H
#define _MUXDEVICE_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../lvgl/lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"
// SCREEN: ui_scrDevice
void ui_scrDevice_screen_init(void);
extern lv_obj_t * ui_scrDevice;
extern lv_obj_t * ui_pnlWall;
extern lv_obj_t * ui_imgWall;
extern lv_obj_t * ui_pnlHeader;
extern lv_obj_t * ui_lblDatetime;
extern lv_obj_t * ui_lblTitle;
extern lv_obj_t * ui_conGlyphs;
extern lv_obj_t * ui_staBluetooth;
extern lv_obj_t * ui_staNetwork;
extern lv_obj_t * ui_staCapacity;
extern lv_obj_t * ui_pnlContent;
extern lv_obj_t * ui_lblRG35XXH;
extern lv_obj_t * ui_lblRG35XXOG;
extern lv_obj_t * ui_lblRG35XXPLUS;
extern lv_obj_t * ui_lblRG35XX2024;
extern lv_obj_t * ui_pnlGlyph;
extern lv_obj_t * ui_icoRG35XXH;
extern lv_obj_t * ui_icoRG35XXOG;
extern lv_obj_t * ui_icoRG35XXPLUS;
extern lv_obj_t * ui_icoRG35XX2024;
extern lv_obj_t * ui_pnlFooter;
extern lv_obj_t * ui_lblNavAGlyph;
extern lv_obj_t * ui_lblNavA;
extern lv_obj_t * ui_lblNavBGlyph;
extern lv_obj_t * ui_lblNavB;
extern lv_obj_t * ui_lblNavCGlyph;
extern lv_obj_t * ui_lblNavC;
extern lv_obj_t * ui_lblNavXGlyph;
extern lv_obj_t * ui_lblNavX;
extern lv_obj_t * ui_lblNavYGlyph;
extern lv_obj_t * ui_lblNavY;
extern lv_obj_t * ui_lblNavZGlyph;
extern lv_obj_t * ui_lblNavZ;
extern lv_obj_t * ui_lblNavMenuGlyph;
extern lv_obj_t * ui_lblNavMenu;
extern lv_obj_t * ui_pnlMessage;
extern lv_obj_t * ui_lblMessage;
extern lv_obj_t * ui_pnlHelp;
extern lv_obj_t * ui_pnlHelpMessage;
extern lv_obj_t * ui_lblHelpHeader;
extern lv_obj_t * ui_lblHelpContent;
extern lv_obj_t * ui_pnlProgress;
extern lv_obj_t * ui_icoProgress;
extern lv_obj_t * ui_barProgress;
extern lv_obj_t * ui____initial_actions0;

LV_IMG_DECLARE(ui_img_nothing_png);    // assets/nothing.png
LV_IMG_DECLARE(ui_img_muoskofi_png);    // assets/muoskofi.png
LV_IMG_DECLARE(ui_img_muoslogotop_png);    // assets/muoslogotop.png
LV_IMG_DECLARE(ui_img_space_png);    // assets/space.png

LV_FONT_DECLARE(ui_font_Awesome);
LV_FONT_DECLARE(ui_font_AwesomeBig);
LV_FONT_DECLARE(ui_font_AwesomeBrand);
LV_FONT_DECLARE(ui_font_AwesomeBrandSmall);
LV_FONT_DECLARE(ui_font_AwesomeSmall);
LV_FONT_DECLARE(ui_font_Gamepad);
LV_FONT_DECLARE(ui_font_GamepadNav);
LV_FONT_DECLARE(ui_font_NotoSans);
LV_FONT_DECLARE(ui_font_NotoSansBig);

void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
