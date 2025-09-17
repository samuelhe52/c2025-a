#pragma once
#include "item_list.h"
#include <cjson/cJSON.h>
#include <stdbool.h>

cJSON* get_store_json();
cJSON* save_list_to_json_object(const ItemList* list);
void initialize_store_file();
void save_object_to_store_file(const cJSON* json);
ItemList* load_items_from_json(const cJSON* json);
int json_get_item_count(const cJSON* json);
cJSON* create_json_item(const Item* item);
bool is_store_file_empty();
