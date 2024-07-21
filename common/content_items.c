#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "content_items.h"

void content_items_initialise_array(struct content_items* item) {
    item->array = (struct ContentItem **)malloc(sizeof(struct ContentItem*));
    item->size = 0;
    item->capacity = 1;
}

void content_items_add_item(struct content_items* item, struct ContentItem* content) {
    if (item->size == item->capacity) {
        item->capacity *= 2;
        item->array = (struct ContentItem**)realloc(item->array, item->capacity * sizeof(struct ContentItem*));
    }

    item->array[item->size] = content;
    item->size++;
}

void content_items_remove_item(struct content_items* item, struct ContentItem* target_item) {
    if (item == NULL || target_item == NULL || item->size == 0) {
        return;
    }

    int index = -1;
    for (int i = 0; i < item->size; ++i) {
        if (item->array[i] == target_item) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        return;
    }

    for (int i = index; i < item->size - 1; ++i) {
        item->array[i] = item->array[i + 1];
    }

    item->size--;

    if (item->size < item->capacity / 2) {
        item->capacity /= 2;
        item->array = (struct ContentItem**)realloc(item->array, item->capacity * sizeof(struct ContentItem*));
    }

    free(target_item);
}

void content_items_free_array(struct content_items* item) {
    for (size_t i = 0; i < item->size; i++) {
        free(item->array[i]);
    }
    free(item->array);
    item->size = 0;
    item->capacity = 0;
}

int content_items_compare_by_name_func(const void* a, const void* b) {
    const struct ContentItem* item1 = *(const struct ContentItem**)a;
    const struct ContentItem* item2 = *(const struct ContentItem**)b;
    return strcasecmp(item1->display_name, item2->display_name);
}

int content_items_compare_by_date_func(const void* a, const void* b) {
    const struct ContentItem* item1 = *(const struct ContentItem**)a;
    const struct ContentItem* item2 = *(const struct ContentItem**)b;
    if (item1->modify_time < item2->modify_time) {
        return 1;
    } else if (item1->modify_time > item2->modify_time) {
        return -1;
    }
    return strcasecmp(item1->display_name, item2->display_name);
}