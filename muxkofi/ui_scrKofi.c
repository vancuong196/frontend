// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: muxkofi

#include "ui.h"

void ui_scrKofi_screen_init(void)
{
    ui_scrKofi = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrKofi, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_SCROLLABLE |
                      LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM);     /// Flags
    lv_obj_set_scrollbar_mode(ui_scrKofi, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_bg_color(ui_scrKofi, lv_color_hex(0x0D0803), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scrKofi, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scrKofi, &ui_font_NotoSans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnlWall = lv_obj_create(ui_scrKofi);
    lv_obj_set_width(ui_pnlWall, 640);
    lv_obj_set_height(ui_pnlWall, 480);
    lv_obj_set_align(ui_pnlWall, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnlWall, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_pnlWall, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgWall = lv_img_create(ui_pnlWall);
    lv_img_set_src(ui_imgWall, &ui_img_muoslogotop_png);
    lv_obj_set_width(ui_imgWall, 640);
    lv_obj_set_height(ui_imgWall, 480);
    lv_obj_set_align(ui_imgWall, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgWall, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgWall, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_img_recolor(ui_imgWall, lv_color_hex(0x100808), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_recolor_opa(ui_imgWall, 175, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnlMessage = lv_obj_create(ui_scrKofi);
    lv_obj_set_width(ui_pnlMessage, 640);
    lv_obj_set_height(ui_pnlMessage, 480);
    lv_obj_set_align(ui_pnlMessage, LV_ALIGN_CENTER);
    lv_obj_set_flex_flow(ui_pnlMessage, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_flex_align(ui_pnlMessage, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnlMessage, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pnlMessage, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlMessage, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_pnlMessage, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblMessageOne = lv_label_create(ui_pnlMessage);
    lv_obj_set_width(ui_lblMessageOne, 615);
    lv_obj_set_height(ui_lblMessageOne, 45);
    lv_obj_set_align(ui_lblMessageOne, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblMessageOne, "Thank you for choosing muOS");
    lv_obj_clear_flag(ui_lblMessageOne, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_lblMessageOne, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_lblMessageOne, LV_DIR_LEFT);
    lv_obj_set_style_text_color(ui_lblMessageOne, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblMessageOne, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_lblMessageOne, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lblMessageOne, &ui_font_NotoSansBig, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblMessageTwo = lv_label_create(ui_pnlMessage);
    lv_obj_set_width(ui_lblMessageTwo, 615);
    lv_obj_set_height(ui_lblMessageTwo, 115);
    lv_obj_set_align(ui_lblMessageTwo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblMessageTwo,
                      "If you would like to support muOS by donating or subscribing that would really help.  This project is done as a hobby.\n\nScan the below QR Code that will take you to the Ko-fi page!");
    lv_obj_clear_flag(ui_lblMessageTwo, LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE |
                      LV_OBJ_FLAG_SNAPPABLE | LV_OBJ_FLAG_SCROLLABLE | LV_OBJ_FLAG_SCROLL_ELASTIC | LV_OBJ_FLAG_SCROLL_MOMENTUM |
                      LV_OBJ_FLAG_SCROLL_CHAIN);     /// Flags
    lv_obj_set_scrollbar_mode(ui_lblMessageTwo, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_scroll_dir(ui_lblMessageTwo, LV_DIR_LEFT);
    lv_obj_set_style_text_color(ui_lblMessageTwo, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblMessageTwo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_lblMessageTwo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgKofi = lv_img_create(ui_pnlMessage);
    lv_img_set_src(ui_imgKofi, &ui_img_muoskofi_png);
    lv_obj_set_width(ui_imgKofi, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_imgKofi, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_imgKofi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgKofi, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgKofi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

}
