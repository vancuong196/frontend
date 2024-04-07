// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: muxassign

#include "ui.h"
#include "ui_helpers.h"

///////////////////// VARIABLES ////////////////////


// SCREEN: ui_scrAssign
void ui_scrAssign_screen_init(void);
lv_obj_t * ui_scrAssign;
lv_obj_t * ui_pnlWall;
lv_obj_t * ui_imgWall;
lv_obj_t * ui_pnlContent;
lv_obj_t * ui_pnlHeader;
lv_obj_t * ui_lblDatetime;
lv_obj_t * ui_lblTitle;
lv_obj_t * ui_conGlyphs;
lv_obj_t * ui_staBluetooth;
lv_obj_t * ui_staNetwork;
lv_obj_t * ui_staCapacity;
lv_obj_t * ui_pnlFooter;
lv_obj_t * ui_lblNavAGlyph;
lv_obj_t * ui_lblNavA;
lv_obj_t * ui_lblNavBGlyph;
lv_obj_t * ui_lblNavB;
lv_obj_t * ui_lblNavCGlyph;
lv_obj_t * ui_lblNavC;
lv_obj_t * ui_lblNavXGlyph;
lv_obj_t * ui_lblNavX;
lv_obj_t * ui_lblNavYGlyph;
lv_obj_t * ui_lblNavY;
lv_obj_t * ui_lblNavZGlyph;
lv_obj_t * ui_lblNavZ;
lv_obj_t * ui_lblNavMenuGlyph;
lv_obj_t * ui_lblNavMenu;
lv_obj_t * ui_lblCoreMessage;
lv_obj_t * ui_pnlMessage;
lv_obj_t * ui_lblMessage;
lv_obj_t * ui_pnlHelp;
lv_obj_t * ui_pnlHelpMessage;
lv_obj_t * ui_lblHelpHeader;
lv_obj_t * ui_lblHelpContent;
lv_obj_t * ui_pnlProgress;
lv_obj_t * ui_icoProgress;
lv_obj_t * ui_barProgress;
lv_obj_t * ui____initial_actions0;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////

void ui_init(void)
{
    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_scrAssign_screen_init();
    ui____initial_actions0 = lv_obj_create(NULL);
    lv_disp_load_scr(ui_scrAssign);
}
