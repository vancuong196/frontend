#pragma once

#include <stddef.h>

typedef enum ContentItemType {
    Directory,
    File
} ContentItemType;

struct ContentItem {
    char* path;
    ContentItemType type;
    char* display_name;
    void* ui_item;
    void* ui_icon;
    void* ui_description;
    long int modify_time;
};

struct content_items {
    struct ContentItem **array;
    int size;
    int capacity;
};

void content_items_initialise_array(struct content_items *item);

void content_items_add_item(struct content_items *item, struct ContentItem* value);

void content_items_free_array(struct content_items *item);

int content_items_compare_by_name_func(const void* a, const void* b);

int content_items_compare_by_date_func(const void* a, const void* b);

void content_items_remove_item(struct content_items* item, struct ContentItem* target_item);