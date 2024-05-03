// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: muxpass

#include "ui.h"

void ui_scrPass_screen_init(void)
{
    ui_scrPass = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_scrPass, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_scrPass, lv_color_hex(0x100808), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_scrPass, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_scrPass, &ui_font_NotoSans, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnlWall = lv_obj_create(ui_scrPass);
    lv_obj_set_width(ui_pnlWall, 640);
    lv_obj_set_height(ui_pnlWall, 480);
    lv_obj_set_align(ui_pnlWall, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnlWall, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pnlWall, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_pnlWall, lv_color_hex(0x0D0803), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_pnlWall, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pnlWall, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_imgWall = lv_img_create(ui_pnlWall);
    lv_img_set_src(ui_imgWall, &ui_img_nothing_png);
    lv_obj_set_width(ui_imgWall, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_imgWall, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_imgWall, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_imgWall, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_imgWall, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_pnlHeader = lv_obj_create(ui_scrPass);
    lv_obj_set_width(ui_pnlHeader, 640);
    lv_obj_set_height(ui_pnlHeader, 42);
    lv_obj_set_align(ui_pnlHeader, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_pnlHeader, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_pnlHeader, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnlHeader, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_pnlHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_pnlHeader, lv_color_hex(0x100808), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlHeader, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_pnlHeader, lv_color_hex(0x0D0803), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_pnlHeader, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnlHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pnlHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pnlHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pnlHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pnlHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblDatetime = lv_label_create(ui_pnlHeader);
    lv_obj_set_height(ui_lblDatetime, 42);
    lv_obj_set_width(ui_lblDatetime, LV_SIZE_CONTENT);   /// 1
    lv_label_set_long_mode(ui_lblDatetime, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_lblDatetime, "");
    lv_obj_add_flag(ui_lblDatetime, LV_OBJ_FLAG_FLOATING);     /// Flags
    lv_obj_set_style_text_color(ui_lblDatetime, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblDatetime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_lblDatetime, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblDatetime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblDatetime, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblDatetime, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblTitle = lv_label_create(ui_pnlHeader);
    lv_obj_set_width(ui_lblTitle, 630);
    lv_obj_set_height(ui_lblTitle, 42);
    lv_obj_set_align(ui_lblTitle, LV_ALIGN_TOP_MID);
    lv_label_set_long_mode(ui_lblTitle, LV_LABEL_LONG_DOT);
    lv_label_set_text(ui_lblTitle, "PASSCODE");
    lv_obj_add_flag(ui_lblTitle, LV_OBJ_FLAG_FLOATING);     /// Flags
    lv_obj_set_style_text_color(ui_lblTitle, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_lblTitle, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_lblTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblTitle, 9, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblTitle, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_conGlyphs = lv_obj_create(ui_pnlHeader);
    lv_obj_remove_style_all(ui_conGlyphs);
    lv_obj_set_width(ui_conGlyphs, 110);
    lv_obj_set_height(ui_conGlyphs, 42);
    lv_obj_set_align(ui_conGlyphs, LV_ALIGN_TOP_RIGHT);
    lv_obj_set_flex_flow(ui_conGlyphs, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_conGlyphs, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_add_flag(ui_conGlyphs, LV_OBJ_FLAG_FLOATING);     /// Flags
    lv_obj_clear_flag(ui_conGlyphs, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_pad_left(ui_conGlyphs, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_conGlyphs, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_conGlyphs, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_conGlyphs, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_pad_left(ui_conGlyphs, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_conGlyphs, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_conGlyphs, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_conGlyphs, 0, LV_PART_SCROLLBAR | LV_STATE_DEFAULT);

    ui_staBluetooth = lv_label_create(ui_conGlyphs);
    lv_obj_set_width(ui_staBluetooth, 20);
    lv_obj_set_height(ui_staBluetooth, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_staBluetooth, -220);
    lv_obj_set_y(ui_staBluetooth, -205);
    lv_obj_set_align(ui_staBluetooth, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_staBluetooth, "");
    lv_obj_set_style_text_color(ui_staBluetooth, lv_color_hex(0xA5B2B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_staBluetooth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_staBluetooth, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_staBluetooth, &ui_font_AwesomeBrand, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_staBluetooth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_staBluetooth, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_staBluetooth, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_staBluetooth, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_staNetwork = lv_label_create(ui_conGlyphs);
    lv_obj_set_width(ui_staNetwork, 30);
    lv_obj_set_height(ui_staNetwork, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_staNetwork, -220);
    lv_obj_set_y(ui_staNetwork, -205);
    lv_obj_set_align(ui_staNetwork, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_staNetwork, "");
    lv_obj_set_style_text_color(ui_staNetwork, lv_color_hex(0xA5B2B5), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_staNetwork, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_staNetwork, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_staNetwork, &ui_font_Awesome, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_staNetwork, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_staNetwork, 6, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_staNetwork, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_staNetwork, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_staCapacity = lv_label_create(ui_conGlyphs);
    lv_obj_set_width(ui_staCapacity, 35);
    lv_obj_set_height(ui_staCapacity, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_staCapacity, -220);
    lv_obj_set_y(ui_staCapacity, -205);
    lv_obj_set_align(ui_staCapacity, LV_ALIGN_TOP_RIGHT);
    lv_label_set_text(ui_staCapacity, "");
    lv_obj_set_style_text_color(ui_staCapacity, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_staCapacity, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_staCapacity, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_staCapacity, &ui_font_AwesomeBig, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_staCapacity, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_staCapacity, -4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_staCapacity, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_staCapacity, 3, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_pnlContent = lv_obj_create(ui_scrPass);
    lv_obj_set_width(ui_pnlContent, 640);
    lv_obj_set_height(ui_pnlContent, 400);
    lv_obj_set_x(ui_pnlContent, 0);
    lv_obj_set_y(ui_pnlContent, 38);
    lv_obj_set_align(ui_pnlContent, LV_ALIGN_TOP_MID);
    lv_obj_set_flex_flow(ui_pnlContent, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(ui_pnlContent, LV_FLEX_ALIGN_SPACE_EVENLY, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnlContent, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_pnlContent, lv_color_hex(0x0D0803), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlContent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnlContent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pnlContent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pnlContent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pnlContent, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pnlContent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_pnlContent, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_pnlContent, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_rolComboOne = lv_roller_create(ui_pnlContent);
    lv_roller_set_options(ui_rolComboOne, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_width(ui_rolComboOne, 80);
    lv_obj_set_height(ui_rolComboOne, 200);
    lv_obj_set_align(ui_rolComboOne, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_rolComboOne, lv_color_hex(0x857B0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboOne, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_rolComboOne, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_rolComboOne, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_rolComboOne, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_rolComboOne, &ui_font_NotoSansBig, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboOne, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboOne, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboOne, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_rolComboOne, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboOne, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_rolComboOne, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_rolComboOne, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_rolComboOne, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_rolComboOne, 5, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_text_color(ui_rolComboOne, lv_color_hex(0xF7E318), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboOne, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboOne, 5, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboOne, lv_color_hex(0x484207), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboOne, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_rolComboTwo = lv_roller_create(ui_pnlContent);
    lv_roller_set_options(ui_rolComboTwo, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_width(ui_rolComboTwo, 80);
    lv_obj_set_height(ui_rolComboTwo, 200);
    lv_obj_set_align(ui_rolComboTwo, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_rolComboTwo, lv_color_hex(0x857B0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboTwo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_rolComboTwo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_rolComboTwo, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_rolComboTwo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_rolComboTwo, &ui_font_NotoSansBig, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboTwo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboTwo, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboTwo, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_rolComboTwo, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboTwo, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_rolComboTwo, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_rolComboTwo, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_rolComboTwo, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_rolComboTwo, 5, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_text_color(ui_rolComboTwo, lv_color_hex(0xF7E318), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboTwo, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboTwo, 5, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboTwo, lv_color_hex(0x484207), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboTwo, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_rolComboThree = lv_roller_create(ui_pnlContent);
    lv_roller_set_options(ui_rolComboThree, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_width(ui_rolComboThree, 80);
    lv_obj_set_height(ui_rolComboThree, 200);
    lv_obj_set_align(ui_rolComboThree, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_rolComboThree, lv_color_hex(0x857B0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboThree, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_rolComboThree, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_rolComboThree, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_rolComboThree, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_rolComboThree, &ui_font_NotoSansBig, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboThree, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboThree, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboThree, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_rolComboThree, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboThree, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_rolComboThree, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_rolComboThree, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_rolComboThree, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_rolComboThree, 5, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_text_color(ui_rolComboThree, lv_color_hex(0xF7E318), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboThree, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboThree, 5, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboThree, lv_color_hex(0x484207), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboThree, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_rolComboFour = lv_roller_create(ui_pnlContent);
    lv_roller_set_options(ui_rolComboFour, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_width(ui_rolComboFour, 80);
    lv_obj_set_height(ui_rolComboFour, 200);
    lv_obj_set_align(ui_rolComboFour, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_rolComboFour, lv_color_hex(0x857B0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboFour, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_rolComboFour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_rolComboFour, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_rolComboFour, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_rolComboFour, &ui_font_NotoSansBig, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboFour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboFour, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboFour, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_rolComboFour, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboFour, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_rolComboFour, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_rolComboFour, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_rolComboFour, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_rolComboFour, 5, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_text_color(ui_rolComboFour, lv_color_hex(0xF7E318), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboFour, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboFour, 5, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboFour, lv_color_hex(0x484207), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboFour, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_rolComboFive = lv_roller_create(ui_pnlContent);
    lv_roller_set_options(ui_rolComboFive, "0\n1\n2\n3\n4\n5\n6\n7\n8\n9", LV_ROLLER_MODE_INFINITE);
    lv_obj_set_width(ui_rolComboFive, 80);
    lv_obj_set_height(ui_rolComboFive, 200);
    lv_obj_set_align(ui_rolComboFive, LV_ALIGN_CENTER);
    lv_obj_set_style_text_color(ui_rolComboFive, lv_color_hex(0x857B0F), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboFive, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui_rolComboFive, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui_rolComboFive, 24, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_rolComboFive, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_rolComboFive, &ui_font_NotoSansBig, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboFive, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboFive, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboFive, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_rolComboFive, LV_BORDER_SIDE_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboFive, 5, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_color(ui_rolComboFive, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_opa(ui_rolComboFive, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_width(ui_rolComboFive, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_outline_pad(ui_rolComboFive, 5, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_text_color(ui_rolComboFive, lv_color_hex(0xF7E318), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_rolComboFive, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui_rolComboFive, 5, LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_rolComboFive, lv_color_hex(0x484207), LV_PART_SELECTED | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_rolComboFive, 255, LV_PART_SELECTED | LV_STATE_DEFAULT);

    ui_pnlFooter = lv_obj_create(ui_scrPass);
    lv_obj_set_width(ui_pnlFooter, 640);
    lv_obj_set_height(ui_pnlFooter, 42);
    lv_obj_set_align(ui_pnlFooter, LV_ALIGN_BOTTOM_MID);
    lv_obj_set_flex_flow(ui_pnlFooter, LV_FLEX_FLOW_ROW);
    lv_obj_set_flex_align(ui_pnlFooter, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER);
    lv_obj_clear_flag(ui_pnlFooter, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_pnlFooter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_pnlFooter, lv_color_hex(0x100808), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlFooter, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_pnlFooter, lv_color_hex(0x0D0803), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_pnlFooter, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnlFooter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pnlFooter, 12, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pnlFooter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pnlFooter, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pnlFooter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_lblMessage = lv_label_create(ui_pnlFooter);
    lv_obj_set_width(ui_lblMessage, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_lblMessage, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_lblMessage, -220);
    lv_obj_set_y(ui_lblMessage, -205);
    lv_obj_set_align(ui_lblMessage, LV_ALIGN_CENTER);
    lv_label_set_text(ui_lblMessage, "");
    lv_label_set_recolor(ui_lblMessage, "true");
    lv_obj_set_style_text_color(ui_lblMessage, lv_color_hex(0xF7E318), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblMessage, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

}