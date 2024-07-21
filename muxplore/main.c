#include "../lvgl/lvgl.h"
#include "../lvgl/drivers/display/fbdev.h"
#include "../lvgl/drivers/indev/evdev.h"
#include "ui/ui.h"
#include <unistd.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/joystick.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <libgen.h>
#include <sys/stat.h>
#include <linux/limits.h>
#include "../common/common.h"
#include "../common/help.h"
#include "../common/options.h"
#include "../common/theme.h"
#include "../common/config.h"
#include "../common/device.h"
#include "../common/glyph.h"
#include "../common/json/json.h"
#include "../common/mini/mini.h"
#include "../common/content_items.h"


char *mux_prog;
struct glyph_config glyph;
struct theme_config theme;

static int js_fd;

int NAV_DPAD_HOR;
int NAV_ANLG_HOR;
int NAV_DPAD_VER;
int NAV_ANLG_VER;
int NAV_A;
int NAV_B;

int turbo_mode = 0;
int msgbox_active = 0;
int input_disable = 0;
int SD2_found = 0;
int nav_sound = 0;
int safe_quit = 0;
int bar_header = 0;
int bar_footer = 0;
char *osd_message;

struct mux_config config;
struct mux_device device;

lv_obj_t *msgbox_element = NULL;

int progress_onscreen = -1;

enum list_module {
    ROOT,
    MMC,
    SDCARD,
    USB,
    FAVOURITE,
    HISTORY
} module;

enum content_type {
    FOLDER,
    ROM
} content;

struct content_items g_file_list;
struct content_items g_dir_list;
struct ContentItem* g_selected_content_item;

lv_group_t *ui_group;
lv_group_t *ui_group_glyph;

int sd_card;
char *sd_dir = NULL;

static char SD1[MAX_BUFFER_SIZE];
static char SD2[MAX_BUFFER_SIZE];
static char E_USB[MAX_BUFFER_SIZE];

char *current_wall = "";

char *prev_dir;
char *curr_dir;

int sys_index = -1;

int ui_count = 0;
int ui_file_count = 0;
int current_item_index = 0;
int first_open = 1;
int nav_moved = 1;
int content_panel_y = 0;

static char current_meta_text[MAX_BUFFER_SIZE];
static char current_content_label[MAX_BUFFER_SIZE];
static char box_image_previous_path[MAX_BUFFER_SIZE];
static char preview_image_previous_path[MAX_BUFFER_SIZE];

lv_timer_t *datetime_timer;
lv_timer_t *capacity_timer;
lv_timer_t *osd_timer;
lv_timer_t *glyph_timer;
lv_timer_t *ui_refresh_timer;

const char *store_catalogue;
const char *store_favourite;

char *load_content_core(int force) {
    char content_core[MAX_BUFFER_SIZE];

    char *card_full;
    switch (module) {
        case MMC:
            card_full = SD1;
            break;
        case SDCARD:
            card_full = SD2;
            break;
        case USB:
            card_full = E_USB;
            break;
        default:
            return NULL;
    }

    if (strcasecmp(get_last_subdir(sd_dir, '/', 4), strip_dir(card_full)) == 0) {
        snprintf(content_core, sizeof(content_core), "%s/MUOS/info/core/core.cfg",
                 device.STORAGE.ROM.MOUNT);
    } else {
        snprintf(content_core, sizeof(content_core), "%s/MUOS/info/core/%s/core.cfg",
                 device.STORAGE.ROM.MOUNT, get_last_subdir(sd_dir, '/', 4));
    }

    if (file_exist(content_core) && !force) {
        printf("LOADING CORE AT: %s\n", content_core);
        return read_text_from_file(content_core);
    } else {
        load_assign(sd_dir, "none");
        safe_quit = 1;
    }

    return NULL;
}

char *load_content_description() {
    if (!g_selected_content_item) {
        return "No Information Found";
    }
    char content_desc[MAX_BUFFER_SIZE];

    const char *content_label = lv_label_get_text(lv_group_get_focused(ui_group));

    switch (module) {
        case ROOT:
            if (strcasecmp(content_label, "SD1 (mmc)") == 0) {
                snprintf(content_desc, sizeof(content_desc), "%s/MUOS/info/catalogue/Root/text/sd1.txt",
                         store_catalogue);
            } else if (strcasecmp(content_label, "SD2 (sdcard)") == 0) {
                snprintf(content_desc, sizeof(content_desc), "%s/MUOS/info/catalogue/Root/text/sd2.txt",
                         store_catalogue);
            }
            break;
        case FAVOURITE:
            char f_core_file[MAX_BUFFER_SIZE];
            char f_pointer[MAX_BUFFER_SIZE];

            snprintf(f_core_file, sizeof(f_core_file), "%s/MUOS/info/favourite/%s", store_favourite, g_selected_content_item->display_name);

            snprintf(f_pointer, sizeof(f_pointer), "%s/MUOS/info/core/%s",
                     device.STORAGE.ROM.MOUNT, get_last_subdir(read_text_from_file(f_core_file), '/', 6));

            snprintf(content_desc, sizeof(content_desc), "%s/MUOS/info/catalogue/%s/text/%s.txt",
                     store_catalogue, read_line_from_file(f_pointer, 5),
                     strip_ext(read_line_from_file(f_pointer, 6)));
            break;
        case HISTORY:
            char h_core_file[MAX_BUFFER_SIZE];
            char h_pointer[MAX_BUFFER_SIZE];

            snprintf(h_core_file, sizeof(h_core_file), "%s/MUOS/info/history/%s", store_favourite, g_selected_content_item->display_name);
            snprintf(h_pointer, sizeof(h_pointer), "%s/MUOS/info/core/%s",
                     device.STORAGE.ROM.MOUNT, get_last_subdir(read_text_from_file(h_core_file), '/', 6));

            snprintf(content_desc, sizeof(content_desc), "%s/MUOS/info/catalogue/%s/text/%s.txt",
                     store_catalogue, read_line_from_file(h_pointer, 5),
                     strip_ext(read_line_from_file(h_pointer, 6)));
            break;
        default:
            char *card_full;
            switch (module) {
                case MMC:
                    card_full = SD1;
                    break;
                case SDCARD:
                    card_full = SD2;
                    break;
                case USB:
                    card_full = E_USB;
                    break;
                default:
                    return NULL;
                    break;
            }

            if (strcasecmp(get_last_subdir(sd_dir, '/', 4), strip_dir(card_full)) == 0) {
                snprintf(content_desc, sizeof(content_desc), "%s/MUOS/info/catalogue/Root/text/%s.txt",
                         store_catalogue, content_label);
            } else {
                char *desc_name = strip_ext(g_selected_content_item->display_name);

                char core_file[MAX_BUFFER_SIZE];
                snprintf(core_file, sizeof(core_file), "%s/MUOS/info/core/%s/core.cfg",
                         device.STORAGE.ROM.MOUNT, get_last_subdir(sd_dir, '/', 4));

                printf("TRYING TO READ CORE CONFIG META: %s\n", core_file);
                char *core_desc = read_line_from_file(core_file, 2);
                if (strlen(core_desc) <= 1 && strcasecmp(desc_name, DUMMY_DIR) != 0) {
                    printf("CORE IS NOT SET - TEXT NOT LOADED\n");
                    return "No Information Found";
                }
                printf("TEXT IS STORED AT: %s\n", core_desc);

                if (strcasecmp(desc_name, DUMMY_DIR) == 0) {
                    snprintf(content_desc, sizeof(content_desc), "%s/MUOS/info/catalogue/Folder/text/%s.txt",
                             store_catalogue, content_label);
                } else {
                    snprintf(content_desc, sizeof(content_desc), "%s/MUOS/info/catalogue/%s/text/%s.txt",
                             store_catalogue, core_desc, desc_name);
                }
            }
            break;
    }

    if (file_exist(content_desc)) {
        snprintf(current_meta_text, sizeof(current_meta_text), "%s", format_meta_text(content_desc));
        return current_meta_text;
    }

    snprintf(current_meta_text, sizeof(current_meta_text), " ");
    return "No Information Found";
}

void image_refresh(char *image_type) {
    if (strcasecmp(image_type, "box") == 0 && config.VISUAL.BOX_ART == 8) {
        printf("BOX ART IS SET TO DISABLED\n");
        return;
    }

    char image[MAX_BUFFER_SIZE];
    char image_path[MAX_BUFFER_SIZE];

    const char *content_label = lv_label_get_text(lv_group_get_focused(ui_group));

    switch (module) {
        case ROOT:
            if (strcasecmp(content_label, "SD1 (mmc)") == 0) {
                snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/Root/%s/sd1.png",
                         store_catalogue, image_type);
                snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/Root/%s/sd1.png",
                         store_catalogue, image_type);
            } else if (strcasecmp(content_label, "SD2 (sdcard)") == 0) {
                snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/Root/%s/sd2.png",
                         store_catalogue, image_type);
                snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/Root/%s/sd2.png",
                         store_catalogue, image_type);
            } else if (strcasecmp(content_label, "USB (external)") == 0) {
                snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/Root/%s/usb.png",
                         store_catalogue, image_type);
                snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/Root/%s/usb.png",
                         store_catalogue, image_type);
            }
            break;
        case FAVOURITE:
            if (!g_selected_content_item) {
                return;
            }
            char f_core_file[MAX_BUFFER_SIZE];
            char f_pointer[MAX_BUFFER_SIZE];

            snprintf(f_core_file, sizeof(f_core_file), "%s/MUOS/info/favourite/%s",
                     store_favourite, g_selected_content_item->display_name);

            snprintf(f_pointer, sizeof(f_pointer), "%s/MUOS/info/core/%s",
                     device.STORAGE.ROM.MOUNT, get_last_subdir(read_text_from_file(f_core_file), '/', 6));

            char *f_core_artwork = read_line_from_file(f_pointer, 3);
            if (strlen(f_core_artwork) <= 1) {
                printf("CORE IS NOT SET - ARTWORK NOT LOADED\n");
                return;
            }

            char *f_file_name = strip_ext(read_line_from_file(f_pointer, 7));

            snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/%s/%s/%s.png",
                     store_catalogue, f_core_artwork, image_type, f_file_name);
            snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/%s/%s/%s.png",
                     store_catalogue, f_core_artwork, image_type, f_file_name);
            break;
        case HISTORY:
            if (!g_selected_content_item) {
                return;
            }
            char h_core_file[MAX_BUFFER_SIZE];
            char h_pointer[MAX_BUFFER_SIZE];

            snprintf(h_core_file, sizeof(h_core_file), "%s/MUOS/info/history/%s", store_favourite, g_selected_content_item->display_name);

            snprintf(h_pointer, sizeof(h_pointer), "%s/MUOS/info/core/%s",
                     device.STORAGE.ROM.MOUNT, get_last_subdir(read_text_from_file(h_core_file), '/', 6));

            char *h_core_artwork = read_line_from_file(h_pointer, 3);
            if (strlen(h_core_artwork) <= 1) {
                printf("CORE IS NOT SET - ARTWORK NOT LOADED\n");
                return;
            }

            char *h_file_name = strip_ext(read_line_from_file(h_pointer, 7));

            snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/%s/%s/%s.png",
                     store_catalogue, h_core_artwork, image_type, h_file_name);
            snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/%s/%s/%s.png",
                     store_catalogue, h_core_artwork, image_type, h_file_name);
            break;
        default:
            char *card_full;
            switch (module) {
                case MMC:
                    card_full = SD1;
                    break;
                case SDCARD:
                    card_full = SD2;
                    break;
                case USB:
                    card_full = E_USB;
                    break;
                default:
                    return;
            }

            if (strcasecmp(get_last_subdir(sd_dir, '/', 4), strip_dir(card_full)) == 0) {
                snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/Folder/%s/%s.png",
                         store_catalogue, image_type, content_label);
                snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/Folder/%s/%s.png",
                         store_catalogue, image_type, content_label);
            } else {
                if (!g_selected_content_item) {
                    return;
                }

                char *file_name = strip_ext(g_selected_content_item->display_name);

                char core_file[MAX_BUFFER_SIZE];
                snprintf(core_file, sizeof(core_file), "%s/muos/INFO/core/%s/core.cfg",
                         device.STORAGE.ROM.MOUNT, get_last_subdir(sd_dir, '/', 4));

                char *core_artwork = read_line_from_file(core_file, 2);
                if (strlen(core_artwork) <= 1 && strcasecmp(file_name, DUMMY_DIR) != 0) {
                    printf("CORE IS NOT SET - ARTWORK NOT LOADED\n");
                    return;
                }

                if (strcasecmp(file_name, DUMMY_DIR) == 0) {
                    snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/Folder/%s/%s.png",
                             store_catalogue, image_type, content_label);
                    snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/Folder/%s/%s.png",
                             store_catalogue, image_type, content_label);
                } else {
                    snprintf(image, sizeof(image), "%s/MUOS/info/catalogue/%s/%s/%s.png",
                             store_catalogue, core_artwork, image_type, file_name);
                    snprintf(image_path, sizeof(image_path), "M:%s/MUOS/info/catalogue/%s/%s/%s.png",
                             store_catalogue, core_artwork, image_type, file_name);
                }
            }
            break;
    }

    if (strcasecmp(image_type, "preview") == 0) {
        if (strcasecmp(preview_image_previous_path, image) != 0) {
            printf("LOADING PREVIEW ARTWORK AT: %s\n", image);

            if (file_exist(image)) {
                lv_img_set_src(ui_imgHelpPreviewImage, image_path);
                snprintf(preview_image_previous_path, sizeof(preview_image_previous_path), "%s", image);
            } else {
                lv_img_set_src(ui_imgHelpPreviewImage, &ui_img_nothing_png);
                snprintf(preview_image_previous_path, sizeof(preview_image_previous_path), " ");
            }
        }
    } else {
        if (strcasecmp(box_image_previous_path, image) != 0) {
            printf("LOADING BOX ARTWORK AT: %s\n", image);

            if (file_exist(image)) {
                lv_img_set_src(ui_imgBox, image_path);
                snprintf(box_image_previous_path, sizeof(box_image_previous_path), "%s", image);
            } else {
                lv_img_set_src(ui_imgBox, &ui_img_nothing_png);
                snprintf(box_image_previous_path, sizeof(box_image_previous_path), " ");
            }
        }
    }
}

void add_directory_and_file_names(const char *base_dir, int *dir_count, int *file_count) {
    struct dirent *entry;

    DIR *dir = opendir(base_dir);
    if (!dir) {
        perror("opendir");
        return;
    }

    char skip_ini[MAX_BUFFER_SIZE];
    snprintf(skip_ini, sizeof(skip_ini), "%s/MUOS/info/skip.ini", device.STORAGE.ROM.MOUNT);
    load_skip_patterns(skip_ini);

    while ((entry = readdir(dir)) != NULL) {
        if (!should_skip(entry->d_name)) {
            struct ContentItem* item = (struct ContentItem*)malloc(sizeof(struct ContentItem));
            if (!item) {
                perror("Memory allocation failed");
                return;
            }

            char file_full_path[PATH_MAX];
            if (entry->d_type == DT_DIR) {
                if (strcasecmp(entry->d_name, ".") != 0 && strcasecmp(entry->d_name, "..") != 0) {
                    char *subdir_path = (char *) malloc(strlen(entry->d_name) + 2);
                    snprintf(subdir_path, strlen(entry->d_name) + 2, "%s", entry->d_name);
                    (*dir_count)++;
                    snprintf(file_full_path, sizeof(file_full_path), "%s/%s", base_dir, entry->d_name);
                    item->path = strdup(file_full_path);
                    item->modify_time = 0;
                    item->type = Directory;
                    item->display_name = subdir_path;
                    content_items_add_item(&g_dir_list, item);
                }
            } else if (entry->d_type == DT_REG) {
                char *file_path = (char *) malloc(strlen(entry->d_name) + 2);
                snprintf(file_path, strlen(entry->d_name) + 2, "%s", entry->d_name);
                (*file_count)++;
                
                snprintf(file_full_path, sizeof(file_full_path), "%s/%s", base_dir, entry->d_name);
                struct stat file_stat;
                if (stat(file_full_path, &file_stat) == 0) {
                    item->modify_time = (long int) file_stat.st_ctime;
                }
                item->path = strdup(file_full_path);
                item->type = File;
                item->display_name = file_path;
                content_items_add_item(&g_file_list, item);
            }
        }
    }

    ui_file_count = *file_count;
    closedir(dir);
}

void content_item_focus_callback(lv_event_t* e) {
    struct ContentItem* content_item = (struct ContentItem*)lv_event_get_user_data(e);
    g_selected_content_item = content_item;
    if (content_item && content_item->ui_item) {
        lv_label_set_long_mode(content_item->ui_description, LV_LABEL_LONG_SCROLL_CIRCULAR);
    }
}

void content_item_defocus_callback(lv_event_t* e) {
    struct ContentItem* content_item = (struct ContentItem*)lv_event_get_user_data(e);
    if (content_item && content_item->ui_item) {
        lv_label_set_long_mode(content_item->ui_description, LV_LABEL_LONG_DOT);
    }
}

void gen_label(int item_type, char *item_glyph, char *item_text, int glyph_pad, struct ContentItem **content_item) {
    lv_obj_t * ui_pnlExplore = lv_obj_create(ui_pnlContent);
    lv_obj_set_width(ui_pnlExplore, device.MUX.WIDTH);
    lv_obj_set_height(ui_pnlExplore, device.MUX.ITEM.HEIGHT);
    lv_obj_set_scrollbar_mode(ui_pnlExplore, LV_SCROLLBAR_MODE_OFF);
    lv_obj_set_style_align(ui_pnlExplore, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_row(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_column(ui_pnlExplore, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * ui_lblExploreItem = lv_label_create(ui_pnlExplore);

    if (item_type == ROM) {
        adjust_visual_label(item_text, config.VISUAL.NAME, config.VISUAL.DASH);
    }
    lv_label_set_text(ui_lblExploreItem, item_text);
    lv_label_set_long_mode(ui_lblExploreItem, LV_LABEL_LONG_DOT);

    lv_obj_set_width(ui_lblExploreItem, device.MUX.WIDTH);
    lv_obj_set_height(ui_lblExploreItem, device.MUX.ITEM.HEIGHT);

    lv_obj_set_style_border_width(ui_lblExploreItem, 5, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_lblExploreItem, LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_color(ui_lblExploreItem, lv_color_hex(theme.SYSTEM.BACKGROUND),
                                   LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_lblExploreItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui_lblExploreItem, LV_GRAD_DIR_HOR, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_lblExploreItem, lv_color_hex(theme.LIST_DEFAULT.BACKGROUND),
                              LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_lblExploreItem, theme.LIST_DEFAULT.BACKGROUND_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_main_stop(ui_lblExploreItem, theme.LIST_DEFAULT.GRADIENT_START,
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_stop(ui_lblExploreItem, theme.LIST_DEFAULT.GRADIENT_STOP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_lblExploreItem, lv_color_hex(theme.LIST_DEFAULT.INDICATOR),
                                  LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_lblExploreItem, theme.LIST_DEFAULT.INDICATOR_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_lblExploreItem, lv_color_hex(theme.LIST_DEFAULT.TEXT),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblExploreItem, theme.LIST_DEFAULT.TEXT_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_color(ui_lblExploreItem, lv_color_hex(theme.LIST_FOCUS.BACKGROUND),
                              LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui_lblExploreItem, theme.LIST_FOCUS.BACKGROUND_ALPHA, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_main_stop(ui_lblExploreItem, theme.LIST_FOCUS.GRADIENT_START, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_grad_stop(ui_lblExploreItem, theme.LIST_FOCUS.GRADIENT_STOP, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(ui_lblExploreItem, lv_color_hex(theme.LIST_FOCUS.INDICATOR),
                                  LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_opa(ui_lblExploreItem, theme.LIST_FOCUS.INDICATOR_ALPHA, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui_lblExploreItem, lv_color_hex(theme.LIST_FOCUS.TEXT),
                                LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_opa(ui_lblExploreItem, theme.LIST_FOCUS.TEXT_ALPHA, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_pad_left(ui_lblExploreItem, 32, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblExploreItem, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblExploreItem, theme.FONT.LIST_PAD_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblExploreItem, theme.FONT.LIST_PAD_BOTTOM, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_line_space(ui_lblExploreItem, 16, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_t * ui_lblExploreItemGlyph = lv_label_create(ui_pnlExplore);
    lv_label_set_text(ui_lblExploreItemGlyph, item_glyph);

    lv_obj_set_width(ui_lblExploreItemGlyph, device.MUX.WIDTH);
    lv_obj_set_height(ui_lblExploreItemGlyph, device.MUX.ITEM.HEIGHT);

    lv_obj_set_style_border_width(ui_lblExploreItemGlyph, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(ui_lblExploreItemGlyph, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_lblExploreItemGlyph, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui_lblExploreItemGlyph, lv_color_hex(theme.LIST_DEFAULT.TEXT),
                                LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_lblExploreItemGlyph, theme.LIST_DEFAULT.TEXT_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_bg_opa(ui_lblExploreItemGlyph, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_opa(ui_lblExploreItemGlyph, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_color(ui_lblExploreItemGlyph, lv_color_hex(theme.LIST_FOCUS.TEXT),
                                LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_text_opa(ui_lblExploreItemGlyph, theme.LIST_FOCUS.TEXT_ALPHA, LV_PART_MAIN | LV_STATE_FOCUSED);

    lv_obj_set_style_pad_left(ui_lblExploreItemGlyph, glyph_pad, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui_lblExploreItemGlyph, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui_lblExploreItemGlyph, theme.FONT.LIST_ICON_PAD_TOP, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui_lblExploreItemGlyph, theme.FONT.LIST_ICON_PAD_BOTTOM,
                                LV_PART_MAIN | LV_STATE_DEFAULT);

    lv_obj_set_style_text_align(ui_lblExploreItemGlyph, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui_lblExploreItemGlyph, &ui_font_AwesomeSmall, LV_PART_MAIN | LV_STATE_DEFAULT);

    if (content_item) {
        (*content_item)->ui_item = ui_pnlExplore;
        (*content_item)->ui_icon = ui_lblExploreItemGlyph;
        (*content_item)->ui_description = ui_lblExploreItem;
        lv_obj_add_event_cb(ui_lblExploreItem, content_item_focus_callback, LV_EVENT_FOCUSED, *content_item);
        lv_obj_add_event_cb(ui_lblExploreItem, content_item_defocus_callback, LV_EVENT_DEFOCUSED, *content_item);
    }

    lv_group_add_obj(ui_group, ui_lblExploreItem);
    lv_group_add_obj(ui_group_glyph, ui_lblExploreItemGlyph);

    if (item_type == FOLDER && strcasecmp(item_text, prev_dir) == 0) {
        sys_index = ui_count;
    }
}

void detect_item_icon(struct ContentItem *item, char **glyph_icon, int *glyph_pad) {
        char fav_dir[PATH_MAX];
        snprintf(fav_dir, sizeof(fav_dir), "%s/MUOS/info/favourite/%s.cfg",
                    store_favourite, strip_ext(item->display_name));

        char hist_dir[PATH_MAX];
        snprintf(hist_dir, sizeof(hist_dir), "%s/MUOS/info/history/%s.cfg",
                    store_favourite, strip_ext(item->display_name));
        if (file_exist(fav_dir)) {
            *glyph_icon = "\uF005";
            *glyph_pad = 10;
        } else if (file_exist(hist_dir)) {
            *glyph_icon = "\uE5A0";
            *glyph_pad = 12;
        } else {
            *glyph_icon = "\uF15B";
            *glyph_pad = 12;
        }
}

void gen_item(int file_count) {
    char init_cache_file[MAX_BUFFER_SIZE];
    char init_meta_dir[MAX_BUFFER_SIZE];

    switch (module) {
        case MMC:
            if (strcasecmp(sd_dir, strip_dir(SD1)) != 0) {
                snprintf(init_cache_file, sizeof(init_cache_file), "%s/MUOS/info/cache/mmc/%s.ini",
                         device.STORAGE.ROM.MOUNT, strchr(strdup(sd_dir), '/') + strlen(SD1));
                snprintf(init_meta_dir, sizeof(init_meta_dir), "%s/MUOS/info/core/%s/",
                         device.STORAGE.ROM.MOUNT, strchr(strdup(sd_dir), '/') + strlen(SD1));
            } else {
                snprintf(init_cache_file, sizeof(init_cache_file), "%s/MUOS/info/cache/root_mmc.ini",
                         device.STORAGE.ROM.MOUNT);
                snprintf(init_meta_dir, sizeof(init_meta_dir), "%s/MUOS/info/core/",
                         device.STORAGE.ROM.MOUNT);
            }
            break;
        case SDCARD:
            if (strcasecmp(sd_dir, strip_dir(SD2)) != 0) {
                snprintf(init_cache_file, sizeof(init_cache_file), "%s/MUOS/info/cache/sdcard/%s.ini",
                         device.STORAGE.ROM.MOUNT, strchr(strdup(sd_dir), '/') + strlen(SD2));
                snprintf(init_meta_dir, sizeof(init_meta_dir), "%s/MUOS/info/core/%s/",
                         device.STORAGE.ROM.MOUNT, strchr(strdup(sd_dir), '/') + strlen(SD2));
            } else {
                snprintf(init_cache_file, sizeof(init_cache_file), "%s/MUOS/info/cache/root_sdcard.ini",
                         device.STORAGE.ROM.MOUNT);
                snprintf(init_meta_dir, sizeof(init_meta_dir), "%s/MUOS/info/core/",
                         device.STORAGE.ROM.MOUNT);
            }
            break;
        case USB:
            if (strcasecmp(sd_dir, strip_dir(E_USB)) != 0) {
                snprintf(init_cache_file, sizeof(init_cache_file), "%s/MUOS/info/cache/usb/%s.ini",
                         device.STORAGE.ROM.MOUNT, strchr(strdup(sd_dir), '/') + strlen(E_USB));
                snprintf(init_meta_dir, sizeof(init_meta_dir), "%s/MUOS/info/core/%s/",
                         device.STORAGE.ROM.MOUNT, strchr(strdup(sd_dir), '/') + strlen(E_USB));
            } else {
                snprintf(init_cache_file, sizeof(init_cache_file), "%s/MUOS/info/cache/root_usb.ini",
                         device.STORAGE.ROM.MOUNT);
                snprintf(init_meta_dir, sizeof(init_meta_dir), "%s/MUOS/info/core/",
                         device.STORAGE.ROM.MOUNT);
            }
            break;
        default:
            break;
    }

    create_directories(strip_dir(init_cache_file));
    create_directories(init_meta_dir);

    char local_name_cache[MAX_BUFFER_SIZE];
    snprintf(local_name_cache, sizeof(local_name_cache), "%score.cfg", init_meta_dir);

    int require_local_name_cache = atoi(read_line_from_file(local_name_cache, 3));

    int is_cache = 0;
    if (file_exist(init_cache_file)) {
        is_cache = 1;
    }

    int fn_valid = 0;
    struct json fn_json;

    char name_file[MAX_BUFFER_SIZE];
    snprintf(name_file, sizeof(name_file), "%s/MUOS/info/name.json",
             device.STORAGE.ROM.MOUNT);

    if (json_valid(read_text_from_file(name_file))) {
        fn_valid = 1;
        fn_json = json_parse(read_text_from_file(name_file));
    }

    for (int i = 0; i < file_count; i++) {
        char fn_name[MAX_BUFFER_SIZE];
        char cache_fn_name[MAX_BUFFER_SIZE];

        if ((require_local_name_cache || module == FAVOURITE || module == HISTORY) && !is_cache && fn_valid) {
            struct json good_name_json = json_object_get(fn_json, strip_ext(g_file_list.array[i]->display_name));
            if (json_exists(good_name_json)) {
                json_string_copy(good_name_json, fn_name, sizeof(fn_name));
                snprintf(cache_fn_name, sizeof(cache_fn_name), "%s\n", fn_name);
                write_text_to_file(init_cache_file, cache_fn_name, "a");
            } else {
                snprintf(fn_name, sizeof(fn_name), "%s", strip_ext((char *) g_file_list.array[i]->display_name));
                snprintf(cache_fn_name, sizeof(cache_fn_name), "%s\n", fn_name);
                write_text_to_file(init_cache_file, cache_fn_name, "a");
                printf("MISSING LABEL: %s", cache_fn_name);
            }
        }
        ui_count++;
    }

    switch (module) {
        case HISTORY:
            qsort(g_file_list.array, g_file_list.size, sizeof(struct ContentItem *), content_items_compare_by_date_func);
            break;
        default:
            qsort(g_file_list.array, g_file_list.size, sizeof(struct ContentItem *), content_items_compare_by_name_func);
            break;
    }

    for (int i = 0; i < g_file_list.size; i++) {

        char *glyph_icon;
        int glyph_pad;
        detect_item_icon(g_file_list.array[i], &glyph_icon, &glyph_pad);
        gen_label(ROM, glyph_icon, strip_ext(g_file_list.array[i]->display_name), glyph_pad, &g_file_list.array[i]);
    }
    puts("FINISH GEN");
}

void create_root_items(char *dir_name) {
    char spec_dir[PATH_MAX];

    int dir_count = 0;

    int file_count = 0;

    switch (module) {
        case FAVOURITE:
            snprintf(spec_dir, sizeof(spec_dir), "%s/MUOS/info/%s",
                     store_favourite, dir_name);

            lv_label_set_text(ui_lblTitle, "FAVOURITES");
            break;
        case HISTORY:
            snprintf(spec_dir, sizeof(spec_dir), "%s/MUOS/info/%s",
                     store_favourite, dir_name);

            lv_label_set_text(ui_lblTitle, "HISTORY");
            break;
        default:
            snprintf(spec_dir, sizeof(spec_dir), "%s/MUOS/info/%s",
                     device.STORAGE.ROM.MOUNT, dir_name);

            lv_label_set_text(ui_lblTitle, "EXPLORE");
            break;
    }

    add_directory_and_file_names(spec_dir, &dir_count, &file_count);

    if (dir_count > 0 || file_count > 0) {
        gen_item(file_count);
    }
}

void create_explore_items(void *count) {
    int *ui_count_ptr = (int *) count;

    char curr_dir[PATH_MAX];
    snprintf(curr_dir, sizeof(curr_dir), "%s", sd_dir);

    int dir_count = 0;
    int file_count = 0;

    switch (module) {
        case MMC:
            lv_label_set_text(ui_lblTitle, "EXPLORE (SD1)");
            break;
        case SDCARD:
            lv_label_set_text(ui_lblTitle, "EXPLORE (SD2)");
            break;
        case USB:
            lv_label_set_text(ui_lblTitle, "EXPLORE (USB)");
            break;
        default:
            lv_label_set_text(ui_lblTitle, "EXPLORE");
            break;
    }

    add_directory_and_file_names(curr_dir, &dir_count, &file_count);

    if (dir_count > 0 || file_count > 0) {
        qsort(g_dir_list.array, g_dir_list.size, sizeof(struct ContentItem *), content_items_compare_by_name_func);
        for (int i = 0; i < dir_count; i++) {
            gen_label(FOLDER, "\uF07B", g_dir_list.array[i]->display_name, 12, &g_dir_list.array[i]);
            (*ui_count_ptr)++;
        }
        gen_item(file_count);
    }
}

void explore_root() {
    lv_label_set_text(ui_lblTitle, "EXPLORE");
    int single_card = 0;

    if (count_items(SD1, DIRECTORIES_ONLY) > 0) {
        single_card += 2;
    }

    if (detect_sd2() && count_items(SD2, DIRECTORIES_ONLY) > 0) {
        single_card += 4;
    }

    if (detect_e_usb() && count_items(E_USB, DIRECTORIES_ONLY) > 0) {
        single_card += 8;
    }

    switch (single_card) {
        case 2:
            write_text_to_file("/tmp/explore_card", "mmc", "w");
            write_text_to_file("/tmp/explore_dir", strip_dir(SD1), "w");
            write_text_to_file("/tmp/single_card", "", "w");
            load_mux("explore");
            safe_quit = 1;
            break;
        case 4:
            write_text_to_file("/tmp/explore_card", "sdcard", "w");
            write_text_to_file("/tmp/explore_dir", strip_dir(SD2), "w");
            write_text_to_file("/tmp/single_card", "", "w");
            load_mux("explore");
            safe_quit = 1;
            break;
        case 6:
            gen_label(FOLDER, "\uF07B", "SD1 (mmc)", 12, NULL);
            gen_label(FOLDER, "\uF07B", "SD2 (sdcard)", 12, NULL);
            ui_count += 2;
            break;
        case 8:
            write_text_to_file("/tmp/explore_card", "usb", "w");
            write_text_to_file("/tmp/explore_dir", strip_dir(E_USB), "w");
            write_text_to_file("/tmp/single_card", "", "w");
            load_mux("explore");
            safe_quit = 1;
            break;
        case 10:
            gen_label(FOLDER, "\uF07B", "SD1 (mmc)", 12, NULL);
            gen_label(FOLDER, "\uF07B", "USB (external)", 12, NULL);
            ui_count += 2;
            break;
        case 12:
            gen_label(FOLDER, "\uF07B", "SD2 (sdcard)", 12, NULL);
            gen_label(FOLDER, "\uF07B", "USB (external)", 12, NULL);
            ui_count += 2;
            break;
        case 14:
            gen_label(FOLDER, "\uF07B", "SD1 (mmc)", 12, NULL);
            gen_label(FOLDER, "\uF07B", "SD2 (sdcard)", 12, NULL);
            gen_label(FOLDER, "\uF07B", "USB (external)", 12, NULL);
            ui_count += 3;
            break;
        default:
            nav_moved = 0;
            lv_obj_clear_flag(ui_lblExploreMessage, LV_OBJ_FLAG_HIDDEN);
            break;
    }
}

void prepare_activity_file(char *act_content, char *act_path) {
    if (!file_exist(act_path)) {
        char activity_content[MAX_BUFFER_SIZE];
        snprintf(activity_content, sizeof(activity_content), "%s\n0\n0", act_content);
        write_text_to_file(act_path, activity_content, "w");
    }
}

int cleanup_content_item_left_over(struct ContentItem *item) {
        char item_history_cfg[MAX_BUFFER_SIZE];
        char item_favorite_cfg[MAX_BUFFER_SIZE];

        char fav_dir[MAX_BUFFER_SIZE];
        char his_dir[MAX_BUFFER_SIZE];

        char * stripped_display_name = strip_ext(item->display_name);
        snprintf(fav_dir, sizeof(fav_dir), "%s/MUOS/info/favourite", store_favourite);
        snprintf(his_dir, sizeof(his_dir), "%s/MUOS/info/history", store_favourite);

        snprintf(item_favorite_cfg, sizeof(item_favorite_cfg), "%s/%s.cfg", fav_dir, stripped_display_name);
        snprintf(item_history_cfg, sizeof(item_history_cfg), "%s/%s.cfg", his_dir, stripped_display_name);

        // cleanup item leftover attempts
        delete_file(item_favorite_cfg);
        delete_file(item_history_cfg);
        return 1;
}

int delete_content(struct ContentItem* item) {
    int result = 1;
    char *hf_msg;
    if (file_exist(item->path)) {
        if (delete_file(item->path)) {
            hf_msg = "Content deleted!";
            cleanup_content_item_left_over(item);
        } else {
            hf_msg = "Cannot delete content!";
            result = 0;
        }
        lv_label_set_text(ui_lblMessage, hf_msg);
        lv_obj_clear_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN);
    }

    return result;
}

int load_content(struct ContentItem *item, int add_favourite) {
    char *assigned_core = load_content_core(0);
    printf("ASSIGNED CORE: %s\n", assigned_core);

    if (assigned_core == NULL) {
        return 0;
    }

    char content_loader_file[MAX_BUFFER_SIZE];
    char * stripped_display_name = strip_ext(item->display_name);
    snprintf(content_loader_file, sizeof(content_loader_file), "%s/MUOS/info/core/%s/%s.cfg",
             device.STORAGE.ROM.MOUNT, get_last_subdir(sd_dir, '/', 4), stripped_display_name);

    printf("CONFIG FILE: %s\n", content_loader_file);

    char *curr_sd;
    switch (module) {
        case USB:
            curr_sd = "usb";
            break;
        case SDCARD:
            curr_sd = "sdcard";
            break;
        default:
            curr_sd = "mmc";
            break;
    }

    if (!file_exist(content_loader_file)) {
        char content_loader_data[MAX_BUFFER_SIZE];
        snprintf(content_loader_data, sizeof(content_loader_data), "%s\n%s\n/mnt/%s/ROMS/\n%s\n%s\n",
                 stripped_display_name, assigned_core, curr_sd,
                 get_last_subdir(sd_dir, '/', 4),
                 item->display_name);

        write_text_to_file(content_loader_file, content_loader_data, "w");
        printf("\nCONFIG DATA\n%s\n", content_loader_data);
    }

    if (file_exist(content_loader_file)) {
        char add_to_hf[MAX_BUFFER_SIZE];
        char *hf_type;

        char fav_dir[MAX_BUFFER_SIZE];
        char his_dir[MAX_BUFFER_SIZE];
        snprintf(fav_dir, sizeof(fav_dir), "%s/MUOS/info/favourite", store_favourite);
        snprintf(his_dir, sizeof(his_dir), "%s/MUOS/info/history", store_favourite);

        if (add_favourite) {
            hf_type = fav_dir;
        } else {
            hf_type = his_dir;
        }

        snprintf(add_to_hf, sizeof(add_to_hf), "%s/%s.cfg", hf_type, stripped_display_name);

        char pointer[MAX_BUFFER_SIZE];
        snprintf(pointer, sizeof(pointer), "%s/MUOS/info/core/%s/%s.cfg",
                 device.STORAGE.ROM.MOUNT, get_last_subdir(sd_dir, '/', 4), stripped_display_name);

        if (add_favourite) {
            // toggle favorite
            char *hf_msg;
            if (file_exist(add_to_hf)) {
                delete_file(add_to_hf);
                if (!file_exist(add_to_hf)) {
                    hf_msg = "Removed from favourites!";
                }
            } else {
                write_text_to_file(add_to_hf, pointer, "w");
                if (file_exist(add_to_hf)) {
                    hf_msg = "Added to favourites!";
                } else {
                    hf_msg = "Could not add to favourites!";
                }
            }

            char *glyph_icon;
            int glyph_pad;
            detect_item_icon(item, &glyph_icon, &glyph_pad);
            lv_label_set_text(item->ui_icon, glyph_icon);
            lv_obj_set_style_pad_left(item->ui_icon, glyph_pad, LV_PART_MAIN | LV_STATE_DEFAULT);

            lv_label_set_text(ui_lblMessage, hf_msg);
            lv_obj_clear_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN);

            return 1;
        } else {
            printf("TRYING TO LOAD CONTENT...\n");
            lv_label_set_text(item->ui_icon, "\uE5A0");
            write_text_to_file(add_to_hf, pointer, "w");
            write_text_to_file(MUOS_ROM_LOAD, read_text_from_file(content_loader_file), "w");
        }

        printf("CONTENT LOADED SUCCESSFULLY\n");
        return 1;
    }

    lv_label_set_text(ui_lblMessage, "Could not load content!");
    lv_obj_clear_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN);

    return 0;
}

int load_cached_content(const char *content_name, char *cache_type, int add_favourite) {
    char pointer_file[MAX_BUFFER_SIZE];
    snprintf(pointer_file, sizeof(pointer_file), "%s/MUOS/info/%s/%s",
             device.STORAGE.ROM.MOUNT, cache_type, content_name);

    if (file_exist(pointer_file)) {
        char cache_file[MAX_BUFFER_SIZE];
        snprintf(cache_file, sizeof(cache_file), "%s",
                 read_line_from_file(pointer_file, 1));

        char add_to_hf[MAX_BUFFER_SIZE];

        if (add_favourite) {
            snprintf(add_to_hf, sizeof(add_to_hf), "%s/MUOS/info/favourite/%s",
                     store_favourite, content_name);

            write_text_to_file(add_to_hf, read_text_from_file(pointer_file), "w");

            return 1;
        } else {
            char *assigned_core = read_line_from_file(cache_file, 2);
            printf("ASSIGNED CORE: %s\n", assigned_core);
            printf("CONFIG FILE: %s\n", cache_file);

            snprintf(add_to_hf, sizeof(add_to_hf), "%s/MUOS/info/history/%s",
                     store_favourite, content_name);

            printf("TRYING TO LOAD CONTENT...\n");
/*
        char act_file[MAX_BUFFER_SIZE];
        char act_content[MAX_BUFFER_SIZE];
        snprintf(act_file, sizeof(act_file), "%s/MUOS/info/activity/%s.act",
                 device.STORAGE.ROM.MOUNT, content_name);
        snprintf(act_content, sizeof(act_content), "%s\n%s\n%s",
                 content_name, curr_sd, read_line_from_file(cache_file, 5));
        prepare_activity_file(act_content, act_file);
*/
            write_text_to_file(add_to_hf, read_text_from_file(pointer_file), "w");
            write_text_to_file(MUOS_ROM_LOAD, read_text_from_file(cache_file), "w");

            printf("CONTENT LOADED SUCCESSFULLY\n");
            return 1;
        }
    }

    lv_label_set_text(ui_lblMessage, "Could not load content!");
    lv_obj_clear_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN);

    return 0;
}

void list_nav_prev(int steps) {
    for (int step = 0; step < steps; ++step) {
        if (current_item_index >= 1 && ui_count > device.MUX.ITEM.COUNT) {
            current_item_index--;
            nav_prev(ui_group, 1);
            nav_prev(ui_group_glyph, 1);
            if (current_item_index > device.MUX.ITEM.PREV_LOW &&
                current_item_index < (ui_count - device.MUX.ITEM.PREV_HIGH)) {
                content_panel_y -= device.MUX.ITEM.PANEL;
                lv_obj_scroll_to_y(ui_pnlContent, content_panel_y, LV_ANIM_OFF);
            }
        } else if (current_item_index >= 0 && ui_count <= device.MUX.ITEM.COUNT) {
            if (current_item_index > 0) {
                current_item_index--;
                nav_prev(ui_group, 1);
                nav_prev(ui_group_glyph, 1);
            }
        }
    }

    play_sound("navigate", nav_sound);
    nav_moved = 1;
}

void list_nav_next(int steps) {
    for (int step = 0; step < steps; ++step) {
        if (current_item_index < (ui_count - 1) && ui_count > device.MUX.ITEM.COUNT) {
            if (current_item_index < (ui_count - 1)) {
                current_item_index++;
                nav_next(ui_group, 1);
                nav_next(ui_group_glyph, 1);
                if (current_item_index >= device.MUX.ITEM.NEXT_HIGH &&
                    current_item_index < (ui_count - device.MUX.ITEM.NEXT_LOW)) {
                    content_panel_y += device.MUX.ITEM.PANEL;
                    lv_obj_scroll_to_y(ui_pnlContent, content_panel_y, LV_ANIM_OFF);
                }
            }
        } else if (current_item_index < ui_count && ui_count <= device.MUX.ITEM.COUNT) {
            if (current_item_index < (ui_count - 1)) {
                current_item_index++;
                nav_next(ui_group, 1);
                nav_next(ui_group_glyph, 1);
            }
        }
    }

    if (first_open) {
        first_open = 0;
    } else {
        play_sound("navigate", nav_sound);
    }
    nav_moved = 1;
}

void cache_message(char *n_dir) {
    char cache_file[MAX_BUFFER_SIZE];
    switch (module) {
        case MMC:
            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/cache/mmc/%s.ini", device.STORAGE.ROM.MOUNT,
                     get_last_subdir(n_dir, '/', 4));
            break;
        case SDCARD:
            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/cache/sdcard/%s.ini", device.STORAGE.ROM.MOUNT,
                     get_last_subdir(n_dir, '/', 4));
            break;
        case USB:
            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/cache/usb/%s.ini", device.STORAGE.ROM.MOUNT,
                     get_last_subdir(n_dir, '/', 4));
            break;
        case FAVOURITE:
            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/cache/favourite.ini", device.STORAGE.ROM.MOUNT);
            break;
        case HISTORY:
            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/cache/history.ini", device.STORAGE.ROM.MOUNT);
            break;
        default:
            break;
    }

    lv_label_set_text(ui_lblMessage, "Loading...");
    lv_obj_clear_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN);
}

void *joystick_task() {
    struct input_event ev;
    int epoll_fd;
    struct epoll_event event, events[device.DEVICE.EVENT];

    int JOYUP_pressed = 0;
    int JOYDOWN_pressed = 0;
    int JOYHOTKEY_pressed = 0;
    int show_delete_confirm = 0;

    int nav_hold = 0;
    int nav_delay = UINT8_MAX;

    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        perror("Error creating EPOLL instance");
        return NULL;
    }

    event.events = EPOLLIN;
    event.data.fd = js_fd;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, js_fd, &event) == -1) {
        perror("Error with EPOLL controller");
        return NULL;
    }

    while (1) {
        int num_events = epoll_wait(epoll_fd, events, device.DEVICE.EVENT, nav_delay);
        if (num_events == -1) {
            perror("Error with EPOLL wait event timer");
            continue;
        }

        for (int i = 0; i < num_events; i++) {
            if (events[i].data.fd == js_fd) {
                int ret = read(js_fd, &ev, sizeof(struct input_event));
                if (ret == -1) {
                    perror("Error reading input");
                    continue;
                }

                switch (ev.type) {
                    case EV_KEY:
                        if (ev.value == 1) {
                            if (msgbox_active) {
                                if (ev.code == NAV_B || ev.code == device.RAW_INPUT.BUTTON.MENU_SHORT) {
                                    play_sound("confirm", nav_sound);
                                    msgbox_active = 0;
                                    progress_onscreen = 0;
                                    lv_obj_add_flag(msgbox_element, LV_OBJ_FLAG_HIDDEN);
                                    show_delete_confirm = 0;
                                } else if (ev.code == NAV_A) {

                                    if (show_delete_confirm) {
                                        play_sound("confirm", nav_sound);
                                        if (g_selected_content_item && delete_content(g_selected_content_item)) {
                                            msgbox_active = 0;
                                            progress_onscreen = 0;
                                            lv_obj_del(g_selected_content_item->ui_item);
                                            lv_obj_add_flag(msgbox_element, LV_OBJ_FLAG_HIDDEN);
                                            show_delete_confirm = 0;
                                            content_items_remove_item(&g_file_list, g_selected_content_item);
                                            g_selected_content_item = NULL;

                                            ui_count--;
                                            if (ui_count <= 0) {
                                                lv_obj_clear_flag(ui_lblExploreMessage, LV_OBJ_FLAG_HIDDEN);
                                            } else {
                                                list_nav_next(1);
                                            }
                                        }
                                        goto nothing_ever_happens;
                                    }

                                    play_sound("confirm", nav_sound);
                                    if (lv_obj_has_flag(ui_pnlHelpPreview, LV_OBJ_FLAG_HIDDEN)) {
                                        lv_obj_add_flag(ui_pnlHelpMessage, LV_OBJ_FLAG_HIDDEN);
                                        lv_obj_clear_flag(ui_pnlHelpPreview, LV_OBJ_FLAG_HIDDEN);
                                    } else {
                                        lv_obj_add_flag(ui_pnlHelpPreview, LV_OBJ_FLAG_HIDDEN);
                                        lv_obj_clear_flag(ui_pnlHelpMessage, LV_OBJ_FLAG_HIDDEN);
                                    }
                                }
                            } else {
                                if (ev.code == device.RAW_INPUT.BUTTON.MENU_LONG) {
                                    JOYHOTKEY_pressed = 1;
                                    JOYUP_pressed = 0;
                                    JOYDOWN_pressed = 0;
                                    nav_delay = UINT8_MAX;
                                    nav_hold = 0;
                                } else if (ev.code == NAV_A) {
                                    if (ui_count == 0) {
                                        goto nothing_ever_happens;
                                    }

                                    play_sound("confirm", nav_sound);

                                    char *content_label = lv_label_get_text(lv_group_get_focused(ui_group));

                                    switch (module) {
                                        case ROOT:
                                            if (strcasecmp(content_label, "SD1 (mmc)") == 0) {
                                                write_text_to_file("/tmp/explore_card", "mmc", "w");
                                                write_text_to_file("/tmp/explore_dir", strip_dir(SD1), "w");
                                                load_mux("explore");
                                                break;
                                            } else if (strcasecmp(content_label, "SD2 (sdcard)") == 0) {
                                                write_text_to_file("/tmp/explore_card", "sdcard", "w");
                                                write_text_to_file("/tmp/explore_dir", strip_dir(SD2), "w");
                                                load_mux("explore");
                                                break;
                                            } else if (strcasecmp(content_label, "USB (external)") == 0) {
                                                write_text_to_file("/tmp/explore_card", "usb", "w");
                                                write_text_to_file("/tmp/explore_dir", strip_dir(E_USB), "w");
                                                load_mux("explore");
                                                break;
                                            }
                                            break;
                                        default:
                                            switch (module) {
                                                case MMC:
                                                case SDCARD:
                                                case USB:
                                                    if (!g_selected_content_item) {
                                                        goto nothing_ever_happens;
                                                    }
                                                    if (g_selected_content_item->type == Directory) {
                                                        char n_dir[MAX_BUFFER_SIZE];
                                                        snprintf(n_dir, sizeof(n_dir), "%s/%s",
                                                                 sd_dir,
                                                                 lv_label_get_text(lv_group_get_focused(ui_group)));

                                                        write_text_to_file("/tmp/explore_dir", n_dir, "w");
                                                        load_mux("explore");

                                                        switch (module) {
                                                            case MMC:
                                                                cache_message(n_dir);
                                                                break;
                                                            case SDCARD:
                                                                cache_message(n_dir);
                                                                break;
                                                            case USB:
                                                                cache_message(n_dir);
                                                                break;
                                                            default:
                                                                break;
                                                        }
                                                        break;
                                                    } else {
                                                        char c_index[MAX_BUFFER_SIZE];
                                                        snprintf(c_index, sizeof(c_index), "%d",
                                                                 current_item_index);
                                                        write_text_to_file(MUOS_IDX_LOAD, c_index, "w");

                                                        if (load_content(g_selected_content_item, 0)) {
                                                            static char launch_script[MAX_BUFFER_SIZE];
                                                            snprintf(launch_script, sizeof(launch_script),
                                                                     "%s/script/mux/launch.sh", INTERNAL_PATH);

                                                            write_text_to_file("/tmp/manual_launch", "1", "w");

                                                            system(launch_script);
                                                        }
                                                        break;
                                                    }
                                                    break;
                                                case FAVOURITE:
                                                    if (!g_selected_content_item) {
                                                        goto nothing_ever_happens;
                                                    }

                                                    load_cached_content(g_selected_content_item->display_name, "favourite", 0);
                                                    write_text_to_file("/tmp/explore_card", "favourite", "w");
                                                    write_text_to_file("/tmp/explore_dir", "", "w");
                                                    write_text_to_file("/tmp/manual_launch", "1", "w");
                                                    break;
                                                case HISTORY:
                                                    if (!g_selected_content_item) {
                                                        goto nothing_ever_happens;
                                                    }
                                                    load_cached_content(g_selected_content_item->display_name, "history", 0);
                                                    write_text_to_file("/tmp/explore_card", "history", "w");
                                                    write_text_to_file("/tmp/explore_dir", "", "w");
                                                    write_text_to_file("/tmp/manual_launch", "1", "w");
                                                default:
                                                    break;
                                            }
                                            break;
                                    }
                                    safe_quit = 1;
                                } else if (ev.code == NAV_B) {
                                    play_sound("back", nav_sound);

                                    switch (module) {
                                        case FAVOURITE:
                                            write_text_to_file("/tmp/explore_card", "root", "w");
                                            write_text_to_file("/tmp/explore_dir", "", "w");
                                            load_mux("launcher");
                                            break;
                                        case HISTORY:
                                            write_text_to_file("/tmp/explore_card", "root", "w");
                                            write_text_to_file("/tmp/explore_dir", "", "w");
                                            load_mux("launcher");
                                            break;
                                        default:
                                            if (sd_dir != NULL) {
                                                char *b_dir = strrchr(sd_dir, '/');
                                                if (b_dir != NULL) {
                                                    if (strcasecmp(str_tolower(b_dir), "/roms") == 0) {
                                                        if (file_exist("/tmp/single_card")) {
                                                            write_text_to_file("/tmp/explore_card", "root", "w");
                                                            write_text_to_file("/tmp/explore_dir", "", "w");
                                                            remove("/tmp/single_card");
                                                            load_mux("launcher");
                                                        } else {
                                                            write_text_to_file("/tmp/explore_card", "root", "w");
                                                            write_text_to_file("/tmp/explore_dir", "", "w");
                                                            load_mux("explore");
                                                        }
                                                    } else {
                                                        write_text_to_file("/tmp/explore_dir",
                                                                           strndup(sd_dir, b_dir - sd_dir), "w");
                                                        load_mux("explore");
                                                    }

                                                }
                                            }
                                            break;
                                    }
                                    safe_quit = 1;
                                } else if (ev.code == device.RAW_INPUT.BUTTON.X) {
                                    if (ui_count == 0) {
                                        goto nothing_ever_happens;
                                    }

                                    char n_dir[MAX_BUFFER_SIZE];
                                    snprintf(n_dir, sizeof(n_dir), "%s", sd_dir);


                                    char cache_file[MAX_BUFFER_SIZE];
                                    switch (module) {
                                        case MMC:
                                            play_sound("confirm", nav_sound);

                                            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/cache/mmc/%s.ini",
                                                     device.STORAGE.ROM.MOUNT, get_last_subdir(n_dir, '/', 4));

                                            write_text_to_file("/tmp/explore_card", "mmc", "w");
                                            break;
                                        case SDCARD:
                                            play_sound("confirm", nav_sound);

                                            snprintf(cache_file, sizeof(cache_file),
                                                     "%s/MUOS/info/cache/sdcard/%s.ini",
                                                     device.STORAGE.ROM.MOUNT, get_last_subdir(n_dir, '/', 4));

                                            write_text_to_file("/tmp/explore_card", "sdcard", "w");
                                            break;
                                        case USB:
                                            play_sound("confirm", nav_sound);

                                            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/cache/usb/%s.ini",
                                                     device.STORAGE.ROM.MOUNT, get_last_subdir(n_dir, '/', 4));

                                            write_text_to_file("/tmp/explore_card", "usb", "w");
                                            break;
                                        case FAVOURITE:
                                            if (!g_selected_content_item) {
                                                goto nothing_ever_happens;
                                            }
                                            play_sound("confirm", nav_sound);

                                            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/favourite/%s.cfg",
                                                     store_favourite, strip_ext(g_selected_content_item->display_name));

                                            remove(cache_file);
                                            write_text_to_file("/tmp/mux_reload", "1", "w");

                                            goto ttq;
                                            break;
                                        case HISTORY:
                                            if (!g_selected_content_item) {
                                                goto nothing_ever_happens;
                                            }
                                            play_sound("confirm", nav_sound);

                                            snprintf(cache_file, sizeof(cache_file), "%s/MUOS/info/history/%s.cfg",
                                                     store_favourite, strip_ext(g_selected_content_item->display_name));

                                            remove(cache_file);
                                            write_text_to_file("/tmp/mux_reload", "1", "w");

                                            goto ttq;
                                            break;
                                        default:
                                            goto nothing_ever_happens;
                                    }

                                    char c_dir[MAX_BUFFER_SIZE];
                                    snprintf(c_dir, sizeof(c_dir), "%s/MUOS/info/core/%s",
                                             device.STORAGE.ROM.MOUNT, get_last_subdir(n_dir, '/', 4));
                                    const char *exception_list[] = {"core.cfg", NULL};

                                    if (file_exist(cache_file)) {
                                        remove(cache_file);
                                        delete_files_of_type(c_dir, "cfg", exception_list);
                                        cache_message(n_dir);
                                    }

                                    write_text_to_file("/tmp/explore_dir", n_dir, "w");
                                    load_mux("explore");

                                    ttq:
                                    safe_quit = 1;
                                } else if (ev.code == device.RAW_INPUT.BUTTON.Y) {
                                    if (!g_selected_content_item) {
                                        goto nothing_ever_happens;
                                    }
                                    play_sound("confirm", nav_sound);
                                    switch (module) {
                                        case MMC:
                                        case SDCARD:
                                        case USB:
                                            if (strcasecmp(g_selected_content_item->display_name, DUMMY_DIR) == 0) {
                                                lv_label_set_text(ui_lblMessage,
                                                                  "Directories cannot be added to Favourites");
                                                lv_obj_clear_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN);
                                                break;
                                            } else {
                                                load_content(g_selected_content_item, 1);
                                                if (file_exist(MUOS_ROM_LOAD)) {
                                                    remove(MUOS_ROM_LOAD);
                                                }
                                                break;
                                            }
                                            break;
                                        case HISTORY:
                                            load_cached_content(g_selected_content_item->display_name, "history", 1);
                                            if (file_exist(MUOS_ROM_LOAD)) {
                                                remove(MUOS_ROM_LOAD);
                                            }
                                            break;
                                        default:
                                            break;
                                    }
                                } else if (ev.code == device.RAW_INPUT.BUTTON.START) {
                                    switch (module) {
                                        case MMC:
                                        case SDCARD:
                                        case USB:
                                            play_sound("confirm", nav_sound);

                                            write_text_to_file("/tmp/explore_card", "root", "w");
                                            remove("/tmp/explore_dir");
                                            load_mux("explore");

                                            safe_quit = 1;
                                            break;
                                        default:
                                            break;
                                    }
                                } else if (ev.code == device.RAW_INPUT.BUTTON.SELECT) {
                                    if (ui_file_count > 0) {
                                        play_sound("confirm", nav_sound);

                                        switch (module) {
                                            case MMC:
                                            case SDCARD:
                                            case USB:
                                                write_text_to_file(MUOS_SAA_LOAD, "1", "w");
                                                load_content_core(1);
                                                break;
                                            default:
                                                break;
                                        }
                                    }
                                } else if (ev.code == device.RAW_INPUT.BUTTON.L1) {
                                    if (current_item_index != 0 && current_item_index < ui_count) {
                                        list_nav_prev(device.MUX.ITEM.COUNT);
                                        lv_task_handler();
                                    }
                                } else if (ev.code == device.RAW_INPUT.BUTTON.R1) {
                                    if (current_item_index >= 0 && current_item_index != ui_count - 1) {
                                        list_nav_next(device.MUX.ITEM.COUNT);
                                        lv_task_handler();
                                    }
                                } else if (ev.code == device.RAW_INPUT.BUTTON.L2)
                                {
                                    JOYHOTKEY_pressed = 0;
                                    if (progress_onscreen == -1) {
                                        if (!g_selected_content_item || g_selected_content_item->type == Directory) {
                                            goto nothing_ever_happens;
                                        }

                                        show_delete_confirm = 1;
                                        play_sound("confirm", nav_sound);
                                        lv_obj_add_flag(ui_pnlHelpPreview, LV_OBJ_FLAG_HIDDEN);
                                        lv_obj_clear_flag(ui_pnlHelpMessage, LV_OBJ_FLAG_HIDDEN);
                                        lv_obj_clear_flag(ui_pnlHelp, LV_OBJ_FLAG_HIDDEN);

                                        static lv_anim_t desc_anim;
                                        static lv_style_t desc_style;
                                        lv_anim_init(&desc_anim);
                                        lv_anim_set_delay(&desc_anim, 2000);
                                        lv_style_init(&desc_style);
                                        lv_style_set_anim(&desc_style, &desc_anim);
                                        lv_obj_add_style(ui_lblHelpDescription, &desc_style, LV_PART_MAIN);
                                        lv_obj_set_style_anim_speed(ui_lblHelpDescription, 25, LV_PART_MAIN);

                                        show_rom_info(ui_pnlHelp, ui_lblHelpHeader, ui_lblHelpPreviewHeader,
                                                    ui_lblHelpDescription,
                                                    lv_label_get_text(lv_group_get_focused(ui_group)),
                                                    "Do you want to delete the content?\nThis will also remove the content from Favorite and History");
                                        lv_label_set_text(ui_lblPreviewHeader, "OK");
                                    }
                                }
                            }
                        } else {
                            if (ev.code == device.RAW_INPUT.BUTTON.MENU_SHORT) {
                                JOYHOTKEY_pressed = 0;
                                if (progress_onscreen == -1) {
                                    if (ui_count == 0) {
                                        goto nothing_ever_happens;
                                    }

                                    play_sound("confirm", nav_sound);
                                    image_refresh("preview");

                                    lv_obj_add_flag(ui_pnlHelpPreview, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_clear_flag(ui_pnlHelpMessage, LV_OBJ_FLAG_HIDDEN);
                                    lv_obj_clear_flag(ui_pnlHelp, LV_OBJ_FLAG_HIDDEN);

                                    static lv_anim_t desc_anim;
                                    static lv_style_t desc_style;
                                    lv_anim_init(&desc_anim);
                                    lv_anim_set_delay(&desc_anim, 2000);
                                    lv_style_init(&desc_style);
                                    lv_style_set_anim(&desc_style, &desc_anim);
                                    lv_obj_add_style(ui_lblHelpDescription, &desc_style, LV_PART_MAIN);
                                    lv_obj_set_style_anim_speed(ui_lblHelpDescription, 25, LV_PART_MAIN);
                                    lv_label_set_text(ui_lblPreviewHeader, "Switch to Preview Image");
                                    show_rom_info(ui_pnlHelp, ui_lblHelpHeader, ui_lblHelpPreviewHeader,
                                                  ui_lblHelpDescription,
                                                  lv_label_get_text(lv_group_get_focused(ui_group)),
                                                  load_content_description());
                                }
                            }
                        }
                    case EV_ABS:
                        if (msgbox_active) {
                            break;
                        }
                        if (ev.code == NAV_DPAD_VER || ev.code == NAV_ANLG_VER) {
                            if ((ev.value >= ((device.INPUT.AXIS_MAX >> 2) * -1) &&
                                 ev.value <= ((device.INPUT.AXIS_MIN >> 2) * -1)) ||
                                ev.value == -1) {
                                if (current_item_index == 0) {
                                    int y = (ui_count - device.MUX.ITEM.COUNT) * device.MUX.ITEM.PANEL;
                                    lv_obj_scroll_to_y(ui_pnlContent, y, LV_ANIM_OFF);
                                    content_panel_y = y;
                                    current_item_index = ui_count - 1;
                                    nav_prev(ui_group, 1);
                                    nav_prev(ui_group_glyph, 1);
                                    image_refresh("box");
                                    lv_task_handler();
                                } else if (current_item_index > 0) {
                                    JOYUP_pressed = (ev.value != 0);
                                    list_nav_prev(1);
                                    lv_task_handler();
                                }
                            } else if ((ev.value >= (device.INPUT.AXIS_MIN >> 2) &&
                                        ev.value <= (device.INPUT.AXIS_MAX >> 2)) ||
                                       ev.value == 1) {
                                if (current_item_index == ui_count - 1) {
                                    lv_obj_scroll_to_y(ui_pnlContent, 0, LV_ANIM_OFF);
                                    content_panel_y = 0;
                                    current_item_index = 0;
                                    nav_next(ui_group, 1);
                                    nav_next(ui_group_glyph, 1);
                                    image_refresh("box");
                                    lv_task_handler();
                                } else if (current_item_index < ui_count - 1) {
                                    JOYDOWN_pressed = (ev.value != 0);
                                    list_nav_next(1);
                                    lv_task_handler();
                                }
                            } else {
                                JOYUP_pressed = 0;
                                JOYDOWN_pressed = 0;
                            }
                        }
                    default:
                    nothing_ever_happens:
                        break;
                }
            }
        }

        if (ui_count > device.MUX.ITEM.COUNT && (JOYUP_pressed || JOYDOWN_pressed)) {
            if (nav_hold > 2) {
                if (nav_delay > 16) {
                    nav_delay -= 16;
                }
                if (JOYUP_pressed && current_item_index > 0) {
                    list_nav_prev(1);
                }
                if (JOYDOWN_pressed && current_item_index < ui_count - 1) {
                    list_nav_next(1);
                }
            }
            nav_hold++;
        } else {
            nav_delay = UINT8_MAX;
            nav_hold = 0;
        }

        if (!atoi(read_line_from_file("/tmp/hdmi_in_use", 1))) {
            if (ev.type == EV_KEY && ev.value == 1 &&
                (ev.code == device.RAW_INPUT.BUTTON.VOLUME_DOWN || ev.code == device.RAW_INPUT.BUTTON.VOLUME_UP)) {
                if (JOYHOTKEY_pressed) {
                    progress_onscreen = 1;
                    lv_obj_add_flag(ui_pnlProgressVolume, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(ui_pnlProgressBrightness, LV_OBJ_FLAG_HIDDEN);
                    lv_label_set_text(ui_icoProgressBrightness, "\uF185");
                    lv_bar_set_value(ui_barProgressBrightness, atoi(read_text_from_file(BRIGHT_PERC)), LV_ANIM_OFF);
                } else {
                    progress_onscreen = 2;
                    lv_obj_add_flag(ui_pnlProgressBrightness, LV_OBJ_FLAG_HIDDEN);
                    lv_obj_clear_flag(ui_pnlProgressVolume, LV_OBJ_FLAG_HIDDEN);
                    int volume = atoi(read_text_from_file(VOLUME_PERC));
                    switch (volume) {
                        case 0:
                            lv_label_set_text(ui_icoProgressVolume, "\uF6A9");
                            break;
                        case 1 ... 46:
                            lv_label_set_text(ui_icoProgressVolume, "\uF026");
                            break;
                        case 47 ... 71:
                            lv_label_set_text(ui_icoProgressVolume, "\uF027");
                            break;
                        case 72 ... 100:
                            lv_label_set_text(ui_icoProgressVolume, "\uF028");
                            break;
                    }
                    lv_bar_set_value(ui_barProgressVolume, volume, LV_ANIM_OFF);
                }
            }
        }

        lv_task_handler();
        usleep(device.SCREEN.WAIT);
    }
}

void set_nav_text(const char *nav_a, const char *nav_b, const char *nav_x, const char *nav_y, const char *nav_menu) {
    lv_label_set_text(ui_lblNavA, nav_a);
    lv_label_set_text(ui_lblNavB, nav_b);
    if (nav_x) lv_label_set_text(ui_lblNavX, nav_x);
    if (nav_y) lv_label_set_text(ui_lblNavY, nav_y);
    lv_label_set_text(ui_lblNavMenu, nav_menu);
}

void set_nav_flag(lv_obj_t *nav_keep[], size_t keep_size, lv_obj_t *nav_hide[], size_t hide_size) {
    for (size_t i = 0; i < hide_size; i++) {
        lv_obj_add_flag(nav_hide[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(nav_hide[i], LV_OBJ_FLAG_FLOATING);
    }
    for (size_t i = 0; i < keep_size; i++) {
        lv_obj_clear_flag(nav_keep[i], LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(nav_keep[i], LV_OBJ_FLAG_FLOATING);
    }
}

void init_elements() {
    switch (config.VISUAL.BOX_ART) {
        case 0: // Bottom + Behind
            lv_obj_set_align(ui_imgBox, LV_ALIGN_BOTTOM_RIGHT);
            lv_obj_move_background(ui_pnlBox);
            lv_obj_move_background(ui_pnlWall);
            break;
        case 1: // Bottom + Front
            lv_obj_set_align(ui_imgBox, LV_ALIGN_BOTTOM_RIGHT);
            lv_obj_move_foreground(ui_pnlBox);
            break;
        case 2: // Middle + Behind
            lv_obj_set_align(ui_imgBox, LV_ALIGN_RIGHT_MID);
            lv_obj_move_background(ui_pnlBox);
            lv_obj_move_background(ui_pnlWall);
            break;
        case 3: // Middle + Front
            lv_obj_set_align(ui_imgBox, LV_ALIGN_RIGHT_MID);
            lv_obj_move_foreground(ui_pnlBox);
            break;
        case 4: // Top + Behind
            lv_obj_set_align(ui_imgBox, LV_ALIGN_TOP_RIGHT);
            lv_obj_move_background(ui_pnlBox);
            lv_obj_move_background(ui_pnlWall);
            break;
        case 5: // Top + Front
            lv_obj_set_align(ui_imgBox, LV_ALIGN_TOP_RIGHT);
            lv_obj_move_foreground(ui_pnlBox);
            break;
        case 6: // Fullscreen + Behind
            lv_obj_set_height(ui_pnlBox, device.MUX.HEIGHT);
            lv_obj_set_align(ui_imgBox, LV_ALIGN_BOTTOM_RIGHT);
            lv_obj_move_background(ui_pnlBox);
            lv_obj_move_background(ui_pnlWall);
            break;
        case 7: // Fullscreen + Front
            lv_obj_set_height(ui_pnlBox, device.MUX.HEIGHT);
            lv_obj_set_align(ui_imgBox, LV_ALIGN_BOTTOM_RIGHT);
            lv_obj_move_foreground(ui_pnlBox);
            break;
        case 8: // Disabled
            lv_obj_add_flag(ui_pnlBox, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_pnlBox, LV_OBJ_FLAG_FLOATING);
            break;
    }

    lv_obj_move_foreground(ui_pnlFooter);
    lv_obj_move_foreground(ui_pnlHeader);
    lv_obj_move_foreground(ui_pnlHelp);
    lv_obj_move_foreground(ui_pnlProgressBrightness);
    lv_obj_move_foreground(ui_pnlProgressVolume);

    if (bar_footer) {
        lv_obj_set_style_bg_opa(ui_pnlFooter, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (bar_header) {
        lv_obj_set_style_bg_opa(ui_pnlHeader, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    process_visual_element(CLOCK, ui_lblDatetime);
    process_visual_element(BLUETOOTH, ui_staBluetooth);
    process_visual_element(NETWORK, ui_staNetwork);
    process_visual_element(BATTERY, ui_staCapacity);

    char *overlay = load_overlay_image();
    if (strlen(overlay) > 0 && theme.MISC.IMAGE_OVERLAY) {
        lv_obj_t * overlay_img = lv_img_create(ui_scrExplore);
        lv_img_set_src(overlay_img, overlay);
        lv_obj_move_foreground(overlay_img);
    }

    switch (module) {
        case ROOT: {
            set_nav_text("Open", "Back", NULL, NULL, "Info");
            lv_obj_t *nav_keep[] = {
                    ui_lblNavAGlyph, ui_lblNavA,
                    ui_lblNavBGlyph, ui_lblNavB,
                    ui_lblNavMenuGlyph, ui_lblNavMenu
            };
            lv_obj_t *nav_hide[] = {
                    ui_lblNavCGlyph, ui_lblNavC,
                    ui_lblNavXGlyph, ui_lblNavX,
                    ui_lblNavYGlyph, ui_lblNavY,
                    ui_lblNavZGlyph, ui_lblNavZ
            };
            set_nav_flag(nav_keep, sizeof(nav_keep) / sizeof(nav_keep[0]), nav_hide,
                         sizeof(nav_hide) / sizeof(nav_hide[0]));
            break;
        }
        case MMC:
        case SDCARD:
        case USB:
        case FAVOURITE:
        case HISTORY: {
            set_nav_text("Open", "Back", module == ROOT ? NULL : "Refresh",
                         module == ROOT ? NULL : "Favourite", "Info");
            if (lv_group_get_obj_count(ui_group) <= 0) {
                lv_obj_t *nav_keep[] = {ui_lblNavBGlyph, ui_lblNavB};
                lv_obj_t *nav_hide[] = {
                        ui_lblNavAGlyph, ui_lblNavA,
                        ui_lblNavCGlyph, ui_lblNavC,
                        ui_lblNavXGlyph, ui_lblNavX,
                        ui_lblNavYGlyph, ui_lblNavY,
                        ui_lblNavZGlyph, ui_lblNavZ,
                        ui_lblNavMenuGlyph, ui_lblNavMenu
                };
                set_nav_flag(nav_keep, sizeof(nav_keep) / sizeof(nav_keep[0]), nav_hide,
                             sizeof(nav_hide) / sizeof(nav_hide[0]));
            } else {
                lv_obj_t *nav_keep[] = {
                        ui_lblNavAGlyph, ui_lblNavA,
                        ui_lblNavBGlyph, ui_lblNavB,
                        ui_lblNavXGlyph, ui_lblNavX,
                        ui_lblNavYGlyph, ui_lblNavY,
                        ui_lblNavMenuGlyph, ui_lblNavMenu
                };
                lv_obj_t *nav_hide[] = {
                        ui_lblNavCGlyph, ui_lblNavC,
                        ui_lblNavZGlyph, ui_lblNavZ
                };
                set_nav_flag(nav_keep, sizeof(nav_keep) / sizeof(nav_keep[0]), nav_hide,
                             sizeof(nav_hide) / sizeof(nav_hide[0]));
            }
            break;
        }
        default:
            break;
    }

    // We'll fucking run it again to ensure 'Favourite' isn't visible in favourites (redundant!)
    switch (module) {
        case FAVOURITE:
            lv_obj_add_flag(ui_lblNavY, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_lblNavY, LV_OBJ_FLAG_FLOATING);
            lv_obj_add_flag(ui_lblNavYGlyph, LV_OBJ_FLAG_HIDDEN);
            lv_obj_add_flag(ui_lblNavYGlyph, LV_OBJ_FLAG_FLOATING);
            lv_label_set_text(ui_lblNavX, "Remove");
            break;
        case HISTORY:
            lv_label_set_text(ui_lblNavX, "Remove");
            break;
        default:
            break;
    }

    if (TEST_IMAGE) display_testing_message(ui_scrExplore);
}

void init_fonts() {
    load_font_text(mux_prog, ui_scrExplore);
}

void glyph_task() {
    // TODO: Bluetooth connectivity!

    if (device.DEVICE.HAS_NETWORK && is_network_connected()) {
        lv_obj_set_style_text_color(ui_staNetwork, lv_color_hex(theme.STATUS.NETWORK.ACTIVE),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_opa(ui_staNetwork, theme.STATUS.NETWORK.ACTIVE_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);
    } else {
        lv_obj_set_style_text_color(ui_staNetwork, lv_color_hex(theme.STATUS.NETWORK.NORMAL),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_opa(ui_staNetwork, theme.STATUS.NETWORK.NORMAL_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (atoi(read_text_from_file(device.BATTERY.CHARGER))) {
        lv_obj_set_style_text_color(ui_staCapacity, lv_color_hex(theme.STATUS.BATTERY.ACTIVE),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_opa(ui_staCapacity, theme.STATUS.BATTERY.ACTIVE_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);
    } else if (read_battery_capacity() <= 15) {
        lv_obj_set_style_text_color(ui_staCapacity, lv_color_hex(theme.STATUS.BATTERY.LOW),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_opa(ui_staCapacity, theme.STATUS.BATTERY.LOW_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);
    } else {
        lv_obj_set_style_text_color(ui_staCapacity, lv_color_hex(theme.STATUS.BATTERY.NORMAL),
                                    LV_PART_MAIN | LV_STATE_DEFAULT);
        lv_obj_set_style_opa(ui_staCapacity, theme.STATUS.BATTERY.NORMAL_ALPHA, LV_PART_MAIN | LV_STATE_DEFAULT);
    }

    if (progress_onscreen > 0) {
        progress_onscreen -= 1;
    } else {
        if (!lv_obj_has_flag(ui_pnlProgressBrightness, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(ui_pnlProgressBrightness, LV_OBJ_FLAG_HIDDEN);
        }
        if (!lv_obj_has_flag(ui_pnlProgressVolume, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(ui_pnlProgressVolume, LV_OBJ_FLAG_HIDDEN);
        }
        if (!msgbox_active) {
            progress_onscreen = -1;
        }
    }
}

void ui_refresh_task() {
    lv_bar_set_value(ui_barProgressBrightness, atoi(read_text_from_file(BRIGHT_PERC)), LV_ANIM_OFF);
    lv_bar_set_value(ui_barProgressVolume, atoi(read_text_from_file(VOLUME_PERC)), LV_ANIM_OFF);

    if (nav_moved) {
        if (lv_group_get_obj_count(ui_group) > 0) {
            static char old_wall[MAX_BUFFER_SIZE];
            static char new_wall[MAX_BUFFER_SIZE];

            snprintf(old_wall, sizeof(old_wall), "%s", current_wall);
            snprintf(new_wall, sizeof(new_wall), "%s", load_wallpaper(
                    ui_scrExplore, ui_group, theme.MISC.ANIMATED_BACKGROUND));

            if (strcasecmp(new_wall, old_wall) != 0) {
                strcpy(current_wall, new_wall);
                if (strlen(new_wall) > 3) {
                    printf("LOADING WALLPAPER: %s\n", new_wall);
                    if (theme.MISC.ANIMATED_BACKGROUND) {
                        lv_obj_t * img = lv_gif_create(ui_pnlWall);
                        lv_gif_set_src(img, new_wall);
                    } else {
                        lv_img_set_src(ui_imgWall, new_wall);
                    }
                    lv_obj_invalidate(ui_pnlWall);
                } else {
                    lv_img_set_src(ui_imgWall, &ui_img_nothing_png);
                }
            }

            static char static_image[MAX_BUFFER_SIZE];
            snprintf(static_image, sizeof(static_image), "%s",
                     load_static_image(ui_scrExplore, ui_group));

            if (strlen(static_image) > 0) {
                printf("LOADING STATIC IMAGE: %s\n", static_image);

                switch (theme.MISC.STATIC_ALIGNMENT) {
                    case 0: // Bottom + Front
                        lv_obj_set_align(ui_imgBox, LV_ALIGN_BOTTOM_RIGHT);
                        lv_obj_move_foreground(ui_pnlBox);
                        break;
                    case 1: // Middle + Front
                        lv_obj_set_align(ui_imgBox, LV_ALIGN_RIGHT_MID);
                        lv_obj_move_foreground(ui_pnlBox);
                        break;
                    case 2: // Top + Front
                        lv_obj_set_align(ui_imgBox, LV_ALIGN_TOP_RIGHT);
                        lv_obj_move_foreground(ui_pnlBox);
                        break;
                    case 3: // Fullscreen + Behind
                        lv_obj_set_height(ui_pnlBox, device.MUX.HEIGHT);
                        lv_obj_set_align(ui_imgBox, LV_ALIGN_BOTTOM_RIGHT);
                        lv_obj_move_background(ui_pnlBox);
                        lv_obj_move_background(ui_pnlWall);
                        break;
                    case 4: // Fullscreen + Front
                        lv_obj_set_height(ui_pnlBox, device.MUX.HEIGHT);
                        lv_obj_set_align(ui_imgBox, LV_ALIGN_BOTTOM_RIGHT);
                        lv_obj_move_foreground(ui_pnlBox);
                        break;
                }

                lv_img_set_src(ui_imgBox, static_image);
            } else {
                lv_img_set_src(ui_imgBox, &ui_img_nothing_png);
            }
        }
        image_refresh("box");
        lv_obj_invalidate(ui_pnlBox);

        const char *content_label = lv_obj_get_user_data(lv_group_get_focused(ui_group));
        snprintf(current_content_label, sizeof(current_content_label), "%s", content_label);

        if (!lv_obj_has_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN)) {
            lv_obj_add_flag(ui_pnlMessage, LV_OBJ_FLAG_HIDDEN);
        }

        nav_moved = 0;
    }
}

int main(int argc, char *argv[]) {
    load_device(&device);
    srand(time(NULL));

    char *cmd_help = "\nmuOS Extras - System List\nUsage: %s <-im>\n\nOptions:\n"
                     "\t-i Index of content to skip to\n"
                     "\t-m List Module:\n"
                     "\t\troot - List SD Cards\n"
                     "\t\tmmc - List directories and files from SD1\n"
                     "\t\tsdcard - List directories and files from SD2\n"
                     "\t\tusb - List directories and files from USB\n"
                     "\t\tfavourite - List favourite items\n"
                     "\t\thistory - List history items\n\n";

    int opt;
    while ((opt = getopt(argc, argv, "i:m:")) != -1) {
        switch (opt) {
            case 'i':
                sys_index = atoi(optarg);
                break;
            case 'm':
                if (strcasecmp(optarg, "root") == 0) {
                    mux_prog = "muxplore";
                    module = ROOT;
                    break;
                } else if (strcasecmp(optarg, "mmc") == 0) {
                    mux_prog = "muxplore";
                    module = MMC;
                    break;
                } else if (strcasecmp(optarg, "sdcard") == 0) {
                    mux_prog = "muxplore";
                    module = SDCARD;
                    break;
                } else if (strcasecmp(optarg, "usb") == 0) {
                    mux_prog = "muxplore";
                    module = USB;
                    break;
                } else if (strcasecmp(optarg, "favourite") == 0) {
                    mux_prog = "muxfavourite";
                    module = FAVOURITE;
                    break;
                } else if (strcasecmp(optarg, "history") == 0) {
                    mux_prog = "muxhistory";
                    module = HISTORY;
                    break;
                } else {
                    printf("Unknown module: %s\n", optarg);
                    return 1;
                }
            default:
                fprintf(stderr, cmd_help, argv[0]);
                return 1;
        }
    }

    if (sys_index == -1) {
        fprintf(stderr, cmd_help, argv[0]);
        return 1;
    }

    lv_init();
    fbdev_init(device.SCREEN.DEVICE);

    static lv_disp_draw_buf_t disp_buf;
    uint32_t disp_buf_size = device.SCREEN.BUFFER;

    lv_color_t * buf1 = (lv_color_t *) malloc(disp_buf_size * sizeof(lv_color_t));
    lv_color_t * buf2 = (lv_color_t *) malloc(disp_buf_size * sizeof(lv_color_t));

    lv_disp_draw_buf_init(&disp_buf, buf1, buf2, disp_buf_size);

    static lv_disp_drv_t disp_drv;
    lv_disp_drv_init(&disp_drv);
    disp_drv.draw_buf = &disp_buf;
    disp_drv.flush_cb = fbdev_flush;
    disp_drv.hor_res = device.SCREEN.WIDTH;
    disp_drv.ver_res = device.SCREEN.HEIGHT;
    disp_drv.sw_rotate = device.SCREEN.ROTATE;
    disp_drv.rotated = device.SCREEN.ROTATE;
    lv_disp_drv_register(&disp_drv);

    load_config(&config);

    ui_init();

    if (file_exist("/tmp/manual_launch")) {
        remove("/tmp/manual_launch");
    }

    store_catalogue = get_default_storage(config.STORAGE.CATALOGUE);
    store_favourite = get_default_storage(config.STORAGE.FAV);

    snprintf(SD1, sizeof(SD1), "%s/ROMS/", device.STORAGE.ROM.MOUNT);
    snprintf(SD2, sizeof(SD2), "%s/ROMS/", device.STORAGE.SDCARD.MOUNT);
    snprintf(E_USB, sizeof(E_USB), "%s/ROMS/", device.STORAGE.USB.MOUNT);

    lv_obj_set_user_data(ui_scrExplore, mux_prog);

    lv_label_set_text(ui_lblDatetime, get_datetime());
    lv_label_set_text(ui_staCapacity, get_capacity());

    load_theme(&theme, &config, &device, mux_prog);
    load_glyph(&glyph, &device, mux_prog);

    apply_theme();
    init_fonts();

    switch (theme.MISC.NAVIGATION_TYPE) {
        case 1:
            NAV_DPAD_HOR = device.RAW_INPUT.DPAD.DOWN;
            NAV_ANLG_HOR = device.RAW_INPUT.ANALOG.LEFT.DOWN;
            NAV_DPAD_VER = device.RAW_INPUT.DPAD.RIGHT;
            NAV_ANLG_VER = device.RAW_INPUT.ANALOG.LEFT.RIGHT;
            break;
        default:
            NAV_DPAD_HOR = device.RAW_INPUT.DPAD.RIGHT;
            NAV_ANLG_HOR = device.RAW_INPUT.ANALOG.LEFT.RIGHT;
            NAV_DPAD_VER = device.RAW_INPUT.DPAD.DOWN;
            NAV_ANLG_VER = device.RAW_INPUT.ANALOG.LEFT.DOWN;
    }

    switch (config.SETTINGS.ADVANCED.SWAP) {
        case 1:
            NAV_A = device.RAW_INPUT.BUTTON.B;
            NAV_B = device.RAW_INPUT.BUTTON.A;
            lv_label_set_text(ui_lblNavAGlyph, "\u21D2");
            lv_label_set_text(ui_lblNavBGlyph, "\u21D3");
            break;
        default:
            NAV_A = device.RAW_INPUT.BUTTON.A;
            NAV_B = device.RAW_INPUT.BUTTON.B;
            lv_label_set_text(ui_lblNavAGlyph, "\u21D3");
            lv_label_set_text(ui_lblNavBGlyph, "\u21D2");
            break;
    }

    current_wall = load_wallpaper(ui_scrExplore, NULL, theme.MISC.ANIMATED_BACKGROUND);
    if (strlen(current_wall) > 3) {
        if (theme.MISC.ANIMATED_BACKGROUND) {
            lv_obj_t * img = lv_gif_create(ui_pnlWall);
            lv_gif_set_src(img, current_wall);
        } else {
            lv_img_set_src(ui_imgWall, current_wall);
        }
    } else {
        lv_img_set_src(ui_imgWall, &ui_img_nothing_png);
    }

    if (config.SETTINGS.GENERAL.SOUND == 2) {
        nav_sound = 1;
    }

    ui_group = lv_group_create();
    ui_group_glyph = lv_group_create();

    content_items_initialise_array(&g_file_list);
    content_items_initialise_array(&g_dir_list);

    if (file_exist(MUOS_PDI_LOAD)) {
        prev_dir = read_text_from_file(MUOS_PDI_LOAD);
    }

    pthread_t gen_item_thread;

    switch (module) {
        case ROOT:
            pthread_create(&gen_item_thread, NULL, (void *) explore_root, (void *) NULL);

            char *SD2_lc = str_tolower(strcpy(malloc(strlen(SD2) + 1), SD2));
            char *USB_lc = str_tolower(strcpy(malloc(strlen(E_USB) + 1), E_USB));

            if (str_startswith(USB_lc, str_tolower(prev_dir))) {
                sys_index = 2;
            } else if (str_startswith(SD2_lc, str_tolower(prev_dir))) {
                sys_index = 1;
            } else {
                sys_index = 0;
            }

            free(SD2_lc);
            free(USB_lc);

            write_text_to_file(MUOS_PDI_LOAD, "explore", "w");
            break;
        case MMC:
        case SDCARD:
        case USB:
            char *ex_file = "/tmp/explore_dir";
            char *ex_path = read_line_from_file(ex_file, 1);
            if (file_exist(ex_file) && ex_path != NULL) {
                int sd1_okay = strncmp(ex_path, strip_dir(SD1), strlen(strip_dir(SD1)));
                int sd2_okay = strncmp(ex_path, strip_dir(SD2), strlen(strip_dir(SD2)));
                int usb_okay = strncmp(ex_path, strip_dir(E_USB), strlen(strip_dir(E_USB)));
                if (sd1_okay == 0 || sd2_okay == 0 || usb_okay == 0) {
                    sd_dir = ex_path;
                    pthread_create(&gen_item_thread, NULL, (void *) create_explore_items,
                                   (void *) &ui_count);
                } else {
                    pthread_create(&gen_item_thread, NULL, (void *) explore_root, (void *) NULL);
                }
            } else {
                switch (module) {
                    case MMC:
                        sd_dir = strip_dir(SD1);
                        pthread_create(&gen_item_thread, NULL, (void *) create_explore_items,
                                       (void *) &ui_count);
                        break;
                    case SDCARD:
                        sd_dir = strip_dir(SD2);
                        pthread_create(&gen_item_thread, NULL, (void *) create_explore_items,
                                       (void *) &ui_count);
                        break;
                    case USB:
                        sd_dir = strip_dir(E_USB);
                        pthread_create(&gen_item_thread, NULL, (void *) create_explore_items,
                                       (void *) &ui_count);
                        break;
                    default:
                        pthread_create(&gen_item_thread, NULL, (void *) explore_root, NULL);
                        break;
                }
            }
            write_text_to_file(MUOS_PDI_LOAD, get_last_dir(sd_dir), "w");
            if (strcasecmp(read_text_from_file(MUOS_PDI_LOAD), "roms") == 0) {
                write_text_to_file(MUOS_PDI_LOAD, get_last_subdir(sd_dir, '/', 4), "w");
            }
            break;
        case FAVOURITE:
            pthread_create(&gen_item_thread, NULL, (void *) create_root_items, "favourite");
            write_text_to_file(MUOS_PDI_LOAD, "favourite", "w");
            break;
        case HISTORY:
            pthread_create(&gen_item_thread, NULL, (void *) create_root_items, "history");
            write_text_to_file(MUOS_PDI_LOAD, "history", "w");
            break;
    }

    struct dt_task_param dt_par;
    struct bat_task_param bat_par;

    dt_par.lblDatetime = ui_lblDatetime;
    bat_par.staCapacity = ui_staCapacity;

    js_fd = open(device.INPUT.EV1, O_RDONLY);
    if (js_fd < 0) {
        perror("Failed to open joystick device");
        return 1;
    }

    lv_indev_drv_t indev_drv;
    lv_indev_drv_init(&indev_drv);

    indev_drv.type = LV_INDEV_TYPE_KEYPAD;
    indev_drv.read_cb = evdev_read;
    indev_drv.user_data = (void *) (intptr_t) js_fd;

    lv_indev_drv_register(&indev_drv);

    datetime_timer = lv_timer_create(datetime_task, UINT16_MAX / 2, &dt_par);
    lv_timer_ready(datetime_timer);

    capacity_timer = lv_timer_create(capacity_task, UINT16_MAX / 2, &bat_par);
    lv_timer_ready(capacity_timer);

    glyph_timer = lv_timer_create(glyph_task, UINT16_MAX / 64, NULL);
    lv_timer_ready(glyph_timer);

    ui_refresh_timer = lv_timer_create(ui_refresh_task, UINT8_MAX / 4, NULL);
    lv_timer_ready(ui_refresh_timer);

    pthread_join(gen_item_thread, NULL);
    if (ui_count > 0) {
        if (ui_count > device.MUX.ITEM.COUNT) {
            lv_obj_t * last_item = lv_obj_get_child(ui_pnlContent, -1);
            lv_obj_set_height(last_item, lv_obj_get_height(last_item) + 50); // Don't bother asking...
        }
        if (sys_index > -1 && sys_index <= ui_count && current_item_index < ui_count) {
            list_nav_next(sys_index);
        } else {
            image_refresh("box");
        }
    } else {
        nav_moved = 0;
        lv_obj_clear_flag(ui_lblExploreMessage, LV_OBJ_FLAG_HIDDEN);
    }
    pthread_cancel(gen_item_thread);

    pthread_t joystick_thread;
    pthread_create(&joystick_thread, NULL, (void *) joystick_task, NULL);

    init_elements();

    while (!safe_quit) {
        usleep(device.SCREEN.WAIT);
    }

    pthread_cancel(joystick_thread);

    close(js_fd);

    return 0;
}

uint32_t mux_tick(void) {
    static uint64_t start_ms = 0;

    if (start_ms == 0) {
        struct timeval tv_start;
        gettimeofday(&tv_start, NULL);
        start_ms = (tv_start.tv_sec * 1000000 + tv_start.tv_usec) / 1000;
    }

    struct timeval tv_now;
    gettimeofday(&tv_now, NULL);

    uint64_t now_ms;
    now_ms = (tv_now.tv_sec * 1000000 + tv_now.tv_usec) / 1000;

    uint32_t time_ms = now_ms - start_ms;
    return time_ms;
}
