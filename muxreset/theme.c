#include "../lvgl/lvgl.h"
#include "ui/ui.h"
#include "../common/theme.h"
#include "../common/glyph.h"

struct theme_config theme;

struct big {
    lv_obj_t *e;
    uint32_t c;
};

struct small {
    lv_obj_t *e;
    int16_t c;
};

void apply_theme() {
    struct big background_elements[] = {
            {ui_scrReset,               theme.SYSTEM.BACKGROUND},
            {ui_pnlFooter,              theme.FOOTER.BACKGROUND},
            {ui_pnlHeader,              theme.HEADER.BACKGROUND},
            {ui_pnlHelpMessage,         theme.HELP.BACKGROUND},
            {ui_lblClearFavourites,     theme.LIST_DEFAULT.BACKGROUND},
            {ui_lblClearHistory,        theme.LIST_DEFAULT.BACKGROUND},
            {ui_lblClearActivity,       theme.LIST_DEFAULT.BACKGROUND},
            {ui_lblClearConfigurations, theme.LIST_DEFAULT.BACKGROUND},
            {ui_lblClearCaches,         theme.LIST_DEFAULT.BACKGROUND},
            {ui_lblRestoreConfig,       theme.LIST_DEFAULT.BACKGROUND},
            {ui_lblRestoreNetwork,      theme.LIST_DEFAULT.BACKGROUND},
            {ui_lblRestorePortMaster,   theme.LIST_DEFAULT.BACKGROUND},
            {ui_pnlMessage,             theme.MESSAGE.BACKGROUND},
            {ui_pnlProgress,            theme.BAR.PANEL_BACKGROUND},
            {ui_barProgress,            theme.BAR.PROGRESS_MAIN_BACKGROUND},
    };
    for (size_t i = 0; i < sizeof(background_elements) / sizeof(background_elements[0]); ++i) {
        lv_obj_set_style_bg_color(background_elements[i].e, lv_color_hex(background_elements[i].c),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small background_alpha_elements[] = {
            {ui_scrReset,       theme.SYSTEM.BACKGROUND_ALPHA},
            {ui_pnlFooter,      theme.FOOTER.BACKGROUND_ALPHA},
            {ui_pnlHeader,      theme.HEADER.BACKGROUND_ALPHA},
            {ui_pnlHelpMessage, theme.HELP.BACKGROUND_ALPHA},
            {ui_pnlMessage,     theme.MESSAGE.BACKGROUND_ALPHA},
            {ui_pnlProgress,    theme.BAR.PANEL_BACKGROUND_ALPHA},
            {ui_barProgress,    theme.BAR.PROGRESS_MAIN_BACKGROUND_ALPHA},
    };
    for (size_t i = 0; i < sizeof(background_alpha_elements) / sizeof(background_alpha_elements[0]); ++i) {
        lv_obj_set_style_bg_opa(background_alpha_elements[i].e, background_alpha_elements[i].c,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct big progress_elements[] = {
            {ui_barProgress, theme.BAR.PROGRESS_ACTIVE_BACKGROUND},
    };
    for (size_t i = 0; i < sizeof(progress_elements) / sizeof(progress_elements[0]); ++i) {
        lv_obj_set_style_bg_color(progress_elements[i].e, lv_color_hex(progress_elements[i].c),
                                  LV_PART_INDICATOR | LV_STATE_DEFAULT);
    }

    struct small progress_alpha_elements[] = {
            {ui_barProgress, theme.BAR.PROGRESS_ACTIVE_BACKGROUND_ALPHA},
    };
    for (size_t i = 0; i < sizeof(progress_alpha_elements) / sizeof(progress_alpha_elements[0]); ++i) {
        lv_obj_set_style_bg_opa(progress_alpha_elements[i].e, progress_alpha_elements[i].c,
                                LV_PART_INDICATOR | LV_STATE_DEFAULT);
    }

    struct big background_focus_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_FOCUS.BACKGROUND},
            {ui_lblClearHistory,        theme.LIST_FOCUS.BACKGROUND},
            {ui_lblClearActivity,       theme.LIST_FOCUS.BACKGROUND},
            {ui_lblClearConfigurations, theme.LIST_FOCUS.BACKGROUND},
            {ui_lblClearCaches,         theme.LIST_FOCUS.BACKGROUND},
            {ui_lblRestoreConfig,       theme.LIST_FOCUS.BACKGROUND},
            {ui_lblRestoreNetwork,      theme.LIST_FOCUS.BACKGROUND},
            {ui_lblRestorePortMaster,   theme.LIST_FOCUS.BACKGROUND},
    };
    for (size_t i = 0; i < sizeof(background_focus_elements) / sizeof(background_focus_elements[0]); ++i) {
        lv_obj_set_style_bg_color(background_focus_elements[i].e, lv_color_hex(background_focus_elements[i].c),
                                  LV_PART_MAIN | LV_STATE_FOCUSED);
    }

    struct big gradient_elements[] = {
            {ui_lblClearFavourites,     theme.SYSTEM.BACKGROUND},
            {ui_lblClearHistory,        theme.SYSTEM.BACKGROUND},
            {ui_lblClearActivity,       theme.SYSTEM.BACKGROUND},
            {ui_lblClearConfigurations, theme.SYSTEM.BACKGROUND},
            {ui_lblClearCaches,         theme.SYSTEM.BACKGROUND},
            {ui_lblRestoreConfig,       theme.SYSTEM.BACKGROUND},
            {ui_lblRestoreNetwork,      theme.SYSTEM.BACKGROUND},
            {ui_lblRestorePortMaster,   theme.SYSTEM.BACKGROUND},
    };
    for (size_t i = 0; i < sizeof(gradient_elements) / sizeof(gradient_elements[0]); ++i) {
        lv_obj_set_style_bg_grad_color(gradient_elements[i].e, lv_color_hex(gradient_elements[i].c),
                                       LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct big indicator_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_DEFAULT.INDICATOR},
            {ui_lblClearHistory,        theme.LIST_DEFAULT.INDICATOR},
            {ui_lblClearActivity,       theme.LIST_DEFAULT.INDICATOR},
            {ui_lblClearConfigurations, theme.LIST_DEFAULT.INDICATOR},
            {ui_lblClearCaches,         theme.LIST_DEFAULT.INDICATOR},
            {ui_lblRestoreConfig,       theme.LIST_DEFAULT.INDICATOR},
            {ui_lblRestoreNetwork,      theme.LIST_DEFAULT.INDICATOR},
            {ui_lblRestorePortMaster,   theme.LIST_DEFAULT.INDICATOR},
    };
    for (size_t i = 0; i < sizeof(indicator_elements) / sizeof(indicator_elements[0]); ++i) {
        lv_obj_set_style_border_color(indicator_elements[i].e, lv_color_hex(indicator_elements[i].c),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct big indicator_focus_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_FOCUS.INDICATOR},
            {ui_lblClearHistory,        theme.LIST_FOCUS.INDICATOR},
            {ui_lblClearActivity,       theme.LIST_FOCUS.INDICATOR},
            {ui_lblClearConfigurations, theme.LIST_FOCUS.INDICATOR},
            {ui_lblClearCaches,         theme.LIST_FOCUS.INDICATOR},
            {ui_lblRestoreConfig,       theme.LIST_FOCUS.INDICATOR},
            {ui_lblRestoreNetwork,      theme.LIST_FOCUS.INDICATOR},
            {ui_lblRestorePortMaster,   theme.LIST_FOCUS.INDICATOR},
    };
    for (size_t i = 0; i < sizeof(indicator_focus_elements) / sizeof(indicator_focus_elements[0]); ++i) {
        lv_obj_set_style_border_color(indicator_focus_elements[i].e, lv_color_hex(indicator_focus_elements[i].c),
                                      LV_PART_MAIN | LV_STATE_FOCUSED);
    }

    struct big default_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_DEFAULT.TEXT},
            {ui_lblClearHistory,        theme.LIST_DEFAULT.TEXT},
            {ui_lblClearActivity,       theme.LIST_DEFAULT.TEXT},
            {ui_lblClearConfigurations, theme.LIST_DEFAULT.TEXT},
            {ui_lblClearCaches,         theme.LIST_DEFAULT.TEXT},
            {ui_lblRestoreConfig,       theme.LIST_DEFAULT.TEXT},
            {ui_lblRestoreNetwork,      theme.LIST_DEFAULT.TEXT},
            {ui_lblRestorePortMaster,   theme.LIST_DEFAULT.TEXT},
            {ui_icoClearFavourites,     theme.LIST_DEFAULT.TEXT},
            {ui_icoClearHistory,        theme.LIST_DEFAULT.TEXT},
            {ui_icoClearActivity,       theme.LIST_DEFAULT.TEXT},
            {ui_icoClearConfigurations, theme.LIST_DEFAULT.TEXT},
            {ui_icoClearCaches,         theme.LIST_DEFAULT.TEXT},
            {ui_icoRestoreConfig,       theme.LIST_DEFAULT.TEXT},
            {ui_icoRestoreNetwork,      theme.LIST_DEFAULT.TEXT},
            {ui_icoRestorePortMaster,   theme.LIST_DEFAULT.TEXT},
            {ui_lblDatetime,            theme.DATETIME.TEXT},
            {ui_lblMessage,             theme.MESSAGE.TEXT},
            {ui_lblTitle,               theme.HEADER.TEXT},
            {ui_lblHelpContent,         theme.HELP.CONTENT},
            {ui_lblHelpHeader,          theme.HELP.TITLE},
            {ui_staBluetooth,           theme.STATUS.BLUETOOTH.NORMAL},
            {ui_staNetwork,             theme.STATUS.NETWORK.NORMAL},
            {ui_staCapacity,            theme.STATUS.BATTERY.NORMAL},
            {ui_lblNavA,                theme.NAV.A.TEXT},
            {ui_lblNavB,                theme.NAV.B.TEXT},
            {ui_lblNavC,                theme.NAV.C.TEXT},
            {ui_lblNavX,                theme.NAV.X.TEXT},
            {ui_lblNavY,                theme.NAV.Y.TEXT},
            {ui_lblNavZ,                theme.NAV.Z.TEXT},
            {ui_lblNavMenu,             theme.NAV.MENU.TEXT},
            {ui_lblNavAGlyph,           theme.NAV.A.GLYPH},
            {ui_lblNavBGlyph,           theme.NAV.B.GLYPH},
            {ui_lblNavCGlyph,           theme.NAV.C.GLYPH},
            {ui_lblNavXGlyph,           theme.NAV.X.GLYPH},
            {ui_lblNavYGlyph,           theme.NAV.Y.GLYPH},
            {ui_lblNavZGlyph,           theme.NAV.Z.GLYPH},
            {ui_lblNavMenuGlyph,        theme.NAV.MENU.GLYPH},
            {ui_icoProgress,            theme.BAR.ICON},
    };
    for (size_t i = 0; i < sizeof(default_elements) / sizeof(default_elements[0]); ++i) {
        lv_obj_set_style_text_color(default_elements[i].e, lv_color_hex(default_elements[i].c),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct big focus_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_FOCUS.TEXT},
            {ui_lblClearHistory,        theme.LIST_FOCUS.TEXT},
            {ui_lblClearActivity,       theme.LIST_FOCUS.TEXT},
            {ui_lblClearConfigurations, theme.LIST_FOCUS.TEXT},
            {ui_lblClearCaches,         theme.LIST_FOCUS.TEXT},
            {ui_lblRestoreConfig,       theme.LIST_FOCUS.TEXT},
            {ui_lblRestoreNetwork,      theme.LIST_FOCUS.TEXT},
            {ui_lblRestorePortMaster,   theme.LIST_FOCUS.TEXT},
            {ui_icoClearFavourites,     theme.LIST_FOCUS.TEXT},
            {ui_icoClearHistory,        theme.LIST_FOCUS.TEXT},
            {ui_icoClearActivity,       theme.LIST_FOCUS.TEXT},
            {ui_icoClearConfigurations, theme.LIST_FOCUS.TEXT},
            {ui_icoClearCaches,         theme.LIST_FOCUS.TEXT},
            {ui_icoRestoreConfig,       theme.LIST_FOCUS.TEXT},
            {ui_icoRestoreNetwork,      theme.LIST_FOCUS.TEXT},
            {ui_icoRestorePortMaster,   theme.LIST_FOCUS.TEXT},
    };
    for (size_t i = 0; i < sizeof(focus_elements) / sizeof(focus_elements[0]); ++i) {
        lv_obj_set_style_text_color(focus_elements[i].e, lv_color_hex(focus_elements[i].c),
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
    }

    struct big border_elements[] = {
            {ui_pnlHelpMessage, theme.HELP.BORDER},
            {ui_pnlMessage,     theme.MESSAGE.BORDER},
            {ui_pnlProgress,    theme.BAR.PANEL_BORDER},
    };
    for (size_t i = 0; i < sizeof(border_elements) / sizeof(border_elements[0]); ++i) {
        lv_obj_set_style_border_color(border_elements[i].e, lv_color_hex(border_elements[i].c),
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small border_alpha_elements[] = {
            {ui_pnlHelpMessage, theme.HELP.BORDER_ALPHA},
            {ui_pnlMessage,     theme.MESSAGE.BORDER_ALPHA},
            {ui_pnlProgress,    theme.BAR.PANEL_BORDER_ALPHA},
    };
    for (size_t i = 0; i < sizeof(border_alpha_elements) / sizeof(border_alpha_elements[0]); ++i) {
        lv_obj_set_style_border_opa(border_alpha_elements[i].e, border_alpha_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small text_default_alpha_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblClearHistory,        theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblClearActivity,       theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblClearConfigurations, theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblClearCaches,         theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblRestoreConfig,       theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblRestoreNetwork,      theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblRestorePortMaster,   theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoClearFavourites,     theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoClearHistory,        theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoClearActivity,       theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoClearConfigurations, theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoClearCaches,         theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoRestoreConfig,       theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoRestoreNetwork,      theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_icoRestorePortMaster,   theme.LIST_DEFAULT.TEXT_ALPHA},
            {ui_lblTitle,               theme.HEADER.TEXT_ALPHA},
            {ui_lblMessage,             theme.MESSAGE.TEXT_ALPHA},
            {ui_lblDatetime,            theme.DATETIME.ALPHA},
            {ui_staBluetooth,           theme.STATUS.BLUETOOTH.NORMAL_ALPHA},
            {ui_staNetwork,             theme.STATUS.NETWORK.NORMAL_ALPHA},
            {ui_staCapacity,            theme.STATUS.BATTERY.NORMAL_ALPHA},
            {ui_lblNavA,                theme.NAV.A.TEXT_ALPHA},
            {ui_lblNavB,                theme.NAV.B.TEXT_ALPHA},
            {ui_lblNavC,                theme.NAV.C.TEXT_ALPHA},
            {ui_lblNavX,                theme.NAV.X.TEXT_ALPHA},
            {ui_lblNavY,                theme.NAV.Y.TEXT_ALPHA},
            {ui_lblNavZ,                theme.NAV.Z.TEXT_ALPHA},
            {ui_lblNavMenu,             theme.NAV.MENU.TEXT_ALPHA},
            {ui_lblNavAGlyph,           theme.NAV.A.GLYPH_ALPHA},
            {ui_lblNavBGlyph,           theme.NAV.B.GLYPH_ALPHA},
            {ui_lblNavCGlyph,           theme.NAV.C.GLYPH_ALPHA},
            {ui_lblNavXGlyph,           theme.NAV.X.GLYPH_ALPHA},
            {ui_lblNavYGlyph,           theme.NAV.Y.GLYPH_ALPHA},
            {ui_lblNavZGlyph,           theme.NAV.Z.GLYPH_ALPHA},
            {ui_lblNavMenuGlyph,        theme.NAV.MENU.GLYPH_ALPHA},
            {ui_icoProgress,            theme.BAR.ICON_ALPHA},
    };
    for (size_t i = 0; i < sizeof(text_default_alpha_elements) / sizeof(text_default_alpha_elements[0]); ++i) {
        lv_obj_set_style_text_opa(text_default_alpha_elements[i].e, text_default_alpha_elements[i].c,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small text_focus_alpha_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_lblClearHistory,        theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_lblClearActivity,       theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_lblClearConfigurations, theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_lblClearCaches,         theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_lblRestoreConfig,       theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_lblRestoreNetwork,      theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_lblRestorePortMaster,   theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoClearFavourites,     theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoClearHistory,        theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoClearActivity,       theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoClearConfigurations, theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoClearCaches,         theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoRestoreConfig,       theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoRestoreNetwork,      theme.LIST_FOCUS.TEXT_ALPHA},
            {ui_icoRestorePortMaster,   theme.LIST_FOCUS.TEXT_ALPHA},
    };
    for (size_t i = 0; i < sizeof(text_focus_alpha_elements) / sizeof(text_focus_alpha_elements[0]); ++i) {
        lv_obj_set_style_text_opa(text_focus_alpha_elements[i].e, text_focus_alpha_elements[i].c,
                                  LV_PART_MAIN | LV_STATE_FOCUSED);
    }

    struct small indicator_default_alpha_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_DEFAULT.INDICATOR_ALPHA},
            {ui_lblClearHistory,        theme.LIST_DEFAULT.INDICATOR_ALPHA},
            {ui_lblClearActivity,       theme.LIST_DEFAULT.INDICATOR_ALPHA},
            {ui_lblClearConfigurations, theme.LIST_DEFAULT.INDICATOR_ALPHA},
            {ui_lblClearCaches,         theme.LIST_DEFAULT.INDICATOR_ALPHA},
            {ui_lblRestoreConfig,       theme.LIST_DEFAULT.INDICATOR_ALPHA},
            {ui_lblRestoreNetwork,      theme.LIST_DEFAULT.INDICATOR_ALPHA},
            {ui_lblRestorePortMaster,   theme.LIST_DEFAULT.INDICATOR_ALPHA},
    };
    for (size_t i = 0;
         i < sizeof(indicator_default_alpha_elements) / sizeof(indicator_default_alpha_elements[0]); ++i) {
        lv_obj_set_style_border_opa(indicator_default_alpha_elements[i].e, indicator_default_alpha_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small indicator_focus_alpha_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_FOCUS.INDICATOR_ALPHA},
            {ui_lblClearHistory,        theme.LIST_FOCUS.INDICATOR_ALPHA},
            {ui_lblClearActivity,       theme.LIST_FOCUS.INDICATOR_ALPHA},
            {ui_lblClearConfigurations, theme.LIST_FOCUS.INDICATOR_ALPHA},
            {ui_lblClearCaches,         theme.LIST_FOCUS.INDICATOR_ALPHA},
            {ui_lblRestoreConfig,       theme.LIST_FOCUS.INDICATOR_ALPHA},
            {ui_lblRestoreNetwork,      theme.LIST_FOCUS.INDICATOR_ALPHA},
            {ui_lblRestorePortMaster,   theme.LIST_FOCUS.INDICATOR_ALPHA},
    };
    for (size_t i = 0; i < sizeof(indicator_focus_alpha_elements) / sizeof(indicator_focus_alpha_elements[0]); ++i) {
        lv_obj_set_style_border_opa(indicator_focus_alpha_elements[i].e, indicator_focus_alpha_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_FOCUSED);
    }

    struct small gradient_stop_default_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_DEFAULT.GRADIENT_STOP},
            {ui_lblClearHistory,        theme.LIST_DEFAULT.GRADIENT_STOP},
            {ui_lblClearActivity,       theme.LIST_DEFAULT.GRADIENT_STOP},
            {ui_lblClearConfigurations, theme.LIST_DEFAULT.GRADIENT_STOP},
            {ui_lblClearCaches,         theme.LIST_DEFAULT.GRADIENT_STOP},
            {ui_lblRestoreConfig,       theme.LIST_DEFAULT.GRADIENT_STOP},
            {ui_lblRestoreNetwork,      theme.LIST_DEFAULT.GRADIENT_STOP},
            {ui_lblRestorePortMaster,   theme.LIST_DEFAULT.GRADIENT_STOP},
    };
    for (size_t i = 0; i < sizeof(gradient_stop_default_elements) / sizeof(gradient_stop_default_elements[0]); ++i) {
        lv_obj_set_style_bg_grad_stop(gradient_stop_default_elements[i].e, gradient_stop_default_elements[i].c,
                                      LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small gradient_stop_focus_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_FOCUS.GRADIENT_STOP},
            {ui_lblClearHistory,        theme.LIST_FOCUS.GRADIENT_STOP},
            {ui_lblClearActivity,       theme.LIST_FOCUS.GRADIENT_STOP},
            {ui_lblClearConfigurations, theme.LIST_FOCUS.GRADIENT_STOP},
            {ui_lblClearCaches,         theme.LIST_FOCUS.GRADIENT_STOP},
            {ui_lblRestoreConfig,       theme.LIST_FOCUS.GRADIENT_STOP},
            {ui_lblRestoreNetwork,      theme.LIST_FOCUS.GRADIENT_STOP},
            {ui_lblRestorePortMaster,   theme.LIST_FOCUS.GRADIENT_STOP},
    };
    for (size_t i = 0; i < sizeof(gradient_stop_focus_elements) / sizeof(gradient_stop_focus_elements[0]); ++i) {
        lv_obj_set_style_bg_grad_stop(gradient_stop_focus_elements[i].e, gradient_stop_focus_elements[i].c,
                                      LV_PART_MAIN | LV_STATE_FOCUSED);
    }

    struct small background_alpha_default_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_DEFAULT.BACKGROUND_ALPHA},
            {ui_lblClearHistory,        theme.LIST_DEFAULT.BACKGROUND_ALPHA},
            {ui_lblClearActivity,       theme.LIST_DEFAULT.BACKGROUND_ALPHA},
            {ui_lblClearConfigurations, theme.LIST_DEFAULT.BACKGROUND_ALPHA},
            {ui_lblClearCaches,         theme.LIST_DEFAULT.BACKGROUND_ALPHA},
            {ui_lblRestoreConfig,       theme.LIST_DEFAULT.BACKGROUND_ALPHA},
            {ui_lblRestoreNetwork,      theme.LIST_DEFAULT.BACKGROUND_ALPHA},
            {ui_lblRestorePortMaster,   theme.LIST_DEFAULT.BACKGROUND_ALPHA},
    };
    for (size_t i = 0;
         i < sizeof(background_alpha_default_elements) / sizeof(background_alpha_default_elements[0]); ++i) {
        lv_obj_set_style_bg_opa(background_alpha_default_elements[i].e, background_alpha_default_elements[i].c,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small background_alpha_focus_elements[] = {
            {ui_lblClearFavourites,     theme.LIST_FOCUS.BACKGROUND_ALPHA},
            {ui_lblClearHistory,        theme.LIST_FOCUS.BACKGROUND_ALPHA},
            {ui_lblClearActivity,       theme.LIST_FOCUS.BACKGROUND_ALPHA},
            {ui_lblClearConfigurations, theme.LIST_FOCUS.BACKGROUND_ALPHA},
            {ui_lblClearCaches,         theme.LIST_FOCUS.BACKGROUND_ALPHA},
            {ui_lblRestoreConfig,       theme.LIST_FOCUS.BACKGROUND_ALPHA},
            {ui_lblRestoreNetwork,      theme.LIST_FOCUS.BACKGROUND_ALPHA},
            {ui_lblRestorePortMaster,   theme.LIST_FOCUS.BACKGROUND_ALPHA},
    };
    for (size_t i = 0; i < sizeof(background_alpha_focus_elements) / sizeof(background_alpha_focus_elements[0]); ++i) {
        lv_obj_set_style_bg_opa(background_alpha_focus_elements[i].e, background_alpha_focus_elements[i].c,
                                LV_PART_MAIN | LV_STATE_FOCUSED);
    }

    struct small radius_elements[] = {
            {ui_pnlHelpMessage, theme.HELP.RADIUS},
            {ui_pnlMessage,     theme.MESSAGE.RADIUS},
            {ui_pnlProgress,    theme.BAR.PANEL_BORDER_RADIUS},
            {ui_barProgress,    theme.BAR.PROGRESS_RADIUS},
    };
    for (size_t i = 0; i < sizeof(radius_elements) / sizeof(radius_elements[0]); ++i) {
        lv_obj_set_style_radius(radius_elements[i].e, radius_elements[i].c,
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_top_header_elements[] = {
            {ui_lblTitle,    theme.FONT.HEADER_PAD_TOP},
            {ui_lblDatetime, theme.FONT.HEADER_PAD_TOP},
    };
    for (size_t i = 0; i < sizeof(font_pad_top_header_elements) / sizeof(font_pad_top_header_elements[0]); ++i) {
        lv_obj_set_style_pad_top(font_pad_top_header_elements[i].e, font_pad_top_header_elements[i].c,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_bottom_header_elements[] = {
            {ui_lblTitle,    theme.FONT.HEADER_PAD_BOTTOM},
            {ui_lblDatetime, theme.FONT.HEADER_PAD_BOTTOM},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_bottom_header_elements) / sizeof(font_pad_bottom_header_elements[0]); ++i) {
        lv_obj_set_style_pad_bottom(font_pad_bottom_header_elements[i].e, font_pad_bottom_header_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_top_footer_elements[] = {
            {ui_lblNavA,    theme.FONT.FOOTER_PAD_TOP},
            {ui_lblNavB,    theme.FONT.FOOTER_PAD_TOP},
            {ui_lblNavC,    theme.FONT.FOOTER_PAD_TOP},
            {ui_lblNavX,    theme.FONT.FOOTER_PAD_TOP},
            {ui_lblNavY,    theme.FONT.FOOTER_PAD_TOP},
            {ui_lblNavZ,    theme.FONT.FOOTER_PAD_TOP},
            {ui_lblNavMenu, theme.FONT.FOOTER_PAD_TOP},
    };
    for (size_t i = 0; i < sizeof(font_pad_top_footer_elements) / sizeof(font_pad_top_footer_elements[0]); ++i) {
        lv_obj_set_style_pad_top(font_pad_top_footer_elements[i].e, font_pad_top_footer_elements[i].c,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_bottom_footer_elements[] = {
            {ui_lblNavA,    theme.FONT.FOOTER_PAD_BOTTOM},
            {ui_lblNavB,    theme.FONT.FOOTER_PAD_BOTTOM},
            {ui_lblNavC,    theme.FONT.FOOTER_PAD_BOTTOM},
            {ui_lblNavX,    theme.FONT.FOOTER_PAD_BOTTOM},
            {ui_lblNavY,    theme.FONT.FOOTER_PAD_BOTTOM},
            {ui_lblNavZ,    theme.FONT.FOOTER_PAD_BOTTOM},
            {ui_lblNavMenu, theme.FONT.FOOTER_PAD_BOTTOM},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_bottom_footer_elements) / sizeof(font_pad_bottom_footer_elements[0]); ++i) {
        lv_obj_set_style_pad_bottom(font_pad_bottom_footer_elements[i].e, font_pad_bottom_footer_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_top_footer_icon_elements[] = {
            {ui_lblNavAGlyph,    theme.FONT.FOOTER_ICON_PAD_TOP},
            {ui_lblNavBGlyph,    theme.FONT.FOOTER_ICON_PAD_TOP},
            {ui_lblNavCGlyph,    theme.FONT.FOOTER_ICON_PAD_TOP},
            {ui_lblNavXGlyph,    theme.FONT.FOOTER_ICON_PAD_TOP},
            {ui_lblNavYGlyph,    theme.FONT.FOOTER_ICON_PAD_TOP},
            {ui_lblNavZGlyph,    theme.FONT.FOOTER_ICON_PAD_TOP},
            {ui_lblNavMenuGlyph, theme.FONT.FOOTER_ICON_PAD_TOP},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_top_footer_icon_elements) / sizeof(font_pad_top_footer_icon_elements[0]); ++i) {
        lv_obj_set_style_pad_top(font_pad_top_footer_icon_elements[i].e, font_pad_top_footer_icon_elements[i].c,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_bottom_footer_icon_elements[] = {
            {ui_lblNavAGlyph,    theme.FONT.FOOTER_ICON_PAD_BOTTOM},
            {ui_lblNavBGlyph,    theme.FONT.FOOTER_ICON_PAD_BOTTOM},
            {ui_lblNavCGlyph,    theme.FONT.FOOTER_ICON_PAD_BOTTOM},
            {ui_lblNavXGlyph,    theme.FONT.FOOTER_ICON_PAD_BOTTOM},
            {ui_lblNavYGlyph,    theme.FONT.FOOTER_ICON_PAD_BOTTOM},
            {ui_lblNavZGlyph,    theme.FONT.FOOTER_ICON_PAD_BOTTOM},
            {ui_lblNavMenuGlyph, theme.FONT.FOOTER_ICON_PAD_BOTTOM},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_bottom_footer_icon_elements) / sizeof(font_pad_bottom_footer_icon_elements[0]); ++i) {
        lv_obj_set_style_pad_bottom(font_pad_bottom_footer_icon_elements[i].e,
                                    font_pad_bottom_footer_icon_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_list_top_elements[] = {
            {ui_lblClearFavourites,     theme.FONT.LIST_PAD_TOP},
            {ui_lblClearHistory,        theme.FONT.LIST_PAD_TOP},
            {ui_lblClearActivity,       theme.FONT.LIST_PAD_TOP},
            {ui_lblClearConfigurations, theme.FONT.LIST_PAD_TOP},
            {ui_lblClearCaches,         theme.FONT.LIST_PAD_TOP},
            {ui_lblRestoreConfig,       theme.FONT.LIST_PAD_TOP},
            {ui_lblRestoreNetwork,      theme.FONT.LIST_PAD_TOP},
            {ui_lblRestorePortMaster,   theme.FONT.LIST_PAD_TOP},
    };
    for (size_t i = 0; i < sizeof(font_pad_list_top_elements) / sizeof(font_pad_list_top_elements[0]); ++i) {
        lv_obj_set_style_pad_top(font_pad_list_top_elements[i].e, font_pad_list_top_elements[i].c,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_list_bottom_elements[] = {
            {ui_lblClearFavourites,     theme.FONT.LIST_PAD_BOTTOM},
            {ui_lblClearHistory,        theme.FONT.LIST_PAD_BOTTOM},
            {ui_lblClearActivity,       theme.FONT.LIST_PAD_BOTTOM},
            {ui_lblClearConfigurations, theme.FONT.LIST_PAD_BOTTOM},
            {ui_lblClearCaches,         theme.FONT.LIST_PAD_BOTTOM},
            {ui_lblRestoreConfig,       theme.FONT.LIST_PAD_BOTTOM},
            {ui_lblRestoreNetwork,      theme.FONT.LIST_PAD_BOTTOM},
            {ui_lblRestorePortMaster,   theme.FONT.LIST_PAD_BOTTOM},
    };
    for (size_t i = 0; i < sizeof(font_pad_list_bottom_elements) / sizeof(font_pad_list_bottom_elements[0]); ++i) {
        lv_obj_set_style_pad_bottom(font_pad_list_bottom_elements[i].e, font_pad_list_bottom_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_top_list_icon_elements[] = {
            {ui_icoClearFavourites,     theme.FONT.LIST_ICON_PAD_TOP},
            {ui_icoClearHistory,        theme.FONT.LIST_ICON_PAD_TOP},
            {ui_icoClearActivity,       theme.FONT.LIST_ICON_PAD_TOP},
            {ui_icoClearConfigurations, theme.FONT.LIST_ICON_PAD_TOP},
            {ui_icoClearCaches,         theme.FONT.LIST_ICON_PAD_TOP},
            {ui_icoRestoreConfig,       theme.FONT.LIST_ICON_PAD_TOP},
            {ui_icoRestoreNetwork,      theme.FONT.LIST_ICON_PAD_TOP},
            {ui_icoRestorePortMaster,   theme.FONT.LIST_ICON_PAD_TOP},
    };
    for (size_t i = 0; i < sizeof(font_pad_top_list_icon_elements) / sizeof(font_pad_top_list_icon_elements[0]); ++i) {
        lv_obj_set_style_pad_top(font_pad_top_list_icon_elements[i].e, font_pad_top_list_icon_elements[i].c,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_bottom_list_icon_elements[] = {
            {ui_icoClearFavourites,     theme.FONT.LIST_ICON_PAD_BOTTOM},
            {ui_icoClearHistory,        theme.FONT.LIST_ICON_PAD_BOTTOM},
            {ui_icoClearActivity,       theme.FONT.LIST_ICON_PAD_BOTTOM},
            {ui_icoClearConfigurations, theme.FONT.LIST_ICON_PAD_BOTTOM},
            {ui_icoClearCaches,         theme.FONT.LIST_ICON_PAD_BOTTOM},
            {ui_icoRestoreConfig,       theme.FONT.LIST_ICON_PAD_BOTTOM},
            {ui_icoRestoreNetwork,      theme.FONT.LIST_ICON_PAD_BOTTOM},
            {ui_icoRestorePortMaster,   theme.FONT.LIST_ICON_PAD_BOTTOM},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_bottom_list_icon_elements) / sizeof(font_pad_bottom_list_icon_elements[0]); ++i) {
        lv_obj_set_style_pad_bottom(font_pad_bottom_list_icon_elements[i].e, font_pad_bottom_list_icon_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_top_header_icon_elements[] = {
            {ui_staBluetooth, theme.FONT.HEADER_ICON_PAD_TOP},
            {ui_staNetwork,   theme.FONT.HEADER_ICON_PAD_TOP},
            {ui_staCapacity,  theme.FONT.HEADER_ICON_PAD_TOP},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_top_header_icon_elements) / sizeof(font_pad_top_header_icon_elements[0]); ++i) {
        lv_obj_set_style_pad_top(font_pad_top_header_icon_elements[i].e, font_pad_top_header_icon_elements[i].c,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_bottom_header_icon_elements[] = {
            {ui_staBluetooth, theme.FONT.HEADER_ICON_PAD_BOTTOM},
            {ui_staNetwork,   theme.FONT.HEADER_ICON_PAD_BOTTOM},
            {ui_staCapacity,  theme.FONT.HEADER_ICON_PAD_BOTTOM},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_bottom_header_icon_elements) / sizeof(font_pad_bottom_header_icon_elements[0]); ++i) {
        lv_obj_set_style_pad_bottom(font_pad_bottom_header_icon_elements[i].e,
                                    font_pad_bottom_header_icon_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_top_message_elements[] = {
            {ui_lblMessage, theme.FONT.MESSAGE_PAD_TOP},
    };
    for (size_t i = 0; i < sizeof(font_pad_top_message_elements) / sizeof(font_pad_top_message_elements[0]); ++i) {
        lv_obj_set_style_pad_top(font_pad_top_message_elements[i].e, font_pad_top_message_elements[i].c,
                                 LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small font_pad_bottom_message_elements[] = {
            {ui_lblMessage, theme.FONT.MESSAGE_PAD_BOTTOM},
    };
    for (size_t i = 0;
         i < sizeof(font_pad_bottom_message_elements) / sizeof(font_pad_bottom_message_elements[0]); ++i) {
        lv_obj_set_style_pad_bottom(font_pad_bottom_message_elements[i].e, font_pad_bottom_message_elements[i].c,
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small content_pad_left_element[] = {
            {ui_pnlContent, theme.MISC.CONTENT.PADDING_LEFT},
            {ui_pnlGlyph,   theme.MISC.CONTENT.PADDING_LEFT},
    };
    for (size_t i = 0; i < sizeof(content_pad_left_element) / sizeof(content_pad_left_element[0]); ++i) {
        lv_obj_set_style_pad_left(content_pad_left_element[i].e, content_pad_left_element[i].c,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small content_pad_right_element[] = {
            {ui_pnlContent, theme.MISC.CONTENT.WIDTH},
            {ui_pnlGlyph,   theme.MISC.CONTENT.WIDTH},
    };
    for (size_t i = 0; i < sizeof(content_pad_right_element) / sizeof(content_pad_right_element[0]); ++i) {
        lv_obj_set_style_width(content_pad_right_element[i].e, content_pad_right_element[i].c,
                               LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small datetime_pad_left_element[] = {
            {ui_lblDatetime, theme.DATETIME.PADDING_LEFT},
    };
    for (size_t i = 0; i < sizeof(datetime_pad_left_element) / sizeof(datetime_pad_left_element[0]); ++i) {
        lv_obj_set_style_pad_left(datetime_pad_left_element[i].e, datetime_pad_left_element[i].c,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small status_pad_right_element[] = {
            {ui_conGlyphs, theme.STATUS.PADDING_RIGHT},
    };
    for (size_t i = 0; i < sizeof(status_pad_right_element) / sizeof(status_pad_right_element[0]); ++i) {
        lv_obj_set_style_pad_right(status_pad_right_element[i].e, status_pad_right_element[i].c,
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    struct small navigation_alignment_element[] = {
            {ui_pnlFooter, theme.NAV.ALIGNMENT},
    };
    for (size_t i = 0; i < sizeof(navigation_alignment_element) / sizeof(navigation_alignment_element[0]); ++i) {
        lv_flex_align_t e_align;
        switch (navigation_alignment_element[i].c) {
            case 1:
                e_align = LV_FLEX_ALIGN_CENTER;
                break;
            case 2:
                e_align = LV_FLEX_ALIGN_END;
                break;
            case 3:
                e_align = LV_FLEX_ALIGN_SPACE_AROUND;
                break;
            case 4:
                e_align = LV_FLEX_ALIGN_SPACE_BETWEEN;
                break;
            case 5:
                e_align = LV_FLEX_ALIGN_SPACE_EVENLY;
                break;
            default:
                e_align = LV_FLEX_ALIGN_START;
                break;
        }
        lv_obj_set_style_flex_main_place(navigation_alignment_element[i].e, e_align, LV_PART_MAIN | LV_STATE_DEFAULT);
    }
}
