// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: muxsysinfo

#ifndef _MUXSYSINFO_UI_H
#define _MUXSYSINFO_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../../lvgl/lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"

// SCREEN: ui_scrSysInfo
void ui_scrSysInfo_screen_init(void);
extern lv_obj_t * ui_scrSysInfo;
extern lv_obj_t * ui_pnlWall;
extern lv_obj_t * ui_imgWall;
extern lv_obj_t * ui_pnlBox;
extern lv_obj_t * ui_imgBox;
extern lv_obj_t * ui_pnlHeader;
extern lv_obj_t * ui_lblDatetime;
extern lv_obj_t * ui_lblTitle;
extern lv_obj_t * ui_conGlyphs;
extern lv_obj_t * ui_staBluetooth;
extern lv_obj_t * ui_staNetwork;
extern lv_obj_t * ui_staCapacity;
extern lv_obj_t * ui_pnlContent;
extern lv_obj_t * ui_lblVersion;
extern lv_obj_t * ui_lblRetro;
extern lv_obj_t * ui_lblKernel;
extern lv_obj_t * ui_lblUptime;
extern lv_obj_t * ui_lblCPU;
extern lv_obj_t * ui_lblSpeed;
extern lv_obj_t * ui_lblGovernor;
extern lv_obj_t * ui_lblMemory;
extern lv_obj_t * ui_lblTemp;
extern lv_obj_t * ui_lblServices;
extern lv_obj_t * ui_lblBatteryCap;
extern lv_obj_t * ui_lblVoltage;
extern lv_obj_t * ui_pnlGlyph;
extern lv_obj_t * ui_icoVersion;
extern lv_obj_t * ui_icoRetro;
extern lv_obj_t * ui_icoKernel;
extern lv_obj_t * ui_icoUptime;
extern lv_obj_t * ui_icoCPU;
extern lv_obj_t * ui_icoSpeed;
extern lv_obj_t * ui_icoGovernor;
extern lv_obj_t * ui_icoMemory;
extern lv_obj_t * ui_icoTemp;
extern lv_obj_t * ui_icoServices;
extern lv_obj_t * ui_icoBatteryCap;
extern lv_obj_t * ui_icoVoltage;
extern lv_obj_t * ui_pnlHighlight;
extern lv_obj_t * ui_lblVersionValue;
extern lv_obj_t * ui_lblRetroValue;
extern lv_obj_t * ui_lblKernelValue;
extern lv_obj_t * ui_lblUptimeValue;
extern lv_obj_t * ui_lblCPUValue;
extern lv_obj_t * ui_lblSpeedValue;
extern lv_obj_t * ui_lblGovernorValue;
extern lv_obj_t * ui_lblMemoryValue;
extern lv_obj_t * ui_lblTempValue;
extern lv_obj_t * ui_lblServicesValue;
extern lv_obj_t * ui_lblBatteryCapValue;
extern lv_obj_t * ui_lblVoltageValue;
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
LV_FONT_DECLARE(ui_font_NotoSansSmall);


void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
