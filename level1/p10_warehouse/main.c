#include <printf.h>
#include <cjson/cJSON.h>
#include "item_list.h"

#define MAX_JSON_SIZE 1048576
#define MAX_ITEM_COUNT 1000

cJSON* get_store_json() {
    FILE* store_file_fp = fopen(WAREHOUSE_STORE_FILE, "r");
    char* json_string = malloc(MAX_JSON_SIZE);
    fgets(json_string, MAX_JSON_SIZE, store_file_fp);

    cJSON* json = cJSON_Parse(json_string);

    fclose(store_file_fp);
    free(json_string);

    if (json == NULL) {
        perror("Error parsing JSON");
        exit(EXIT_FAILURE);
    }
    return json;
}

ItemList* load_items_from_json(const cJSON* json) {
    const cJSON* json_items = cJSON_GetObjectItemCaseSensitive(json, "items");
    const cJSON* json_item = NULL;
    ItemList* list = item_list_create();

    if (!cJSON_IsArray(json_items)) {
        perror("Error parsing JSON: \"items\" is not array");
        exit(EXIT_FAILURE);
    }

    cJSON_ArrayForEach(json_item, json_items) {
        const cJSON* id = cJSON_GetObjectItemCaseSensitive(json_item, "id");
        const cJSON* name = cJSON_GetObjectItemCaseSensitive(json_item, "name");
        const cJSON* quantity = cJSON_GetObjectItemCaseSensitive(json_item, "quantity");
        const cJSON* price = cJSON_GetObjectItemCaseSensitive(json_item, "price");

        Item* item = create_item(id->valueint, name->valuestring, quantity->valueint, price->valuedouble);
        item_list_add(list, item);
        free(item);
    }

    return list;
}

int get_item_count(const cJSON* json) {
    const cJSON* json_items = cJSON_GetObjectItemCaseSensitive(json, "items");
    if (!cJSON_IsArray(json_items)) {
        perror("Error parsing JSON: \"items\" is not array");
        exit(EXIT_FAILURE);
    }
    return cJSON_GetArraySize(json_items);
}

cJSON* create_json_item(const Item* item) {
    cJSON* json_item = cJSON_CreateObject();
    cJSON_AddNumberToObject(json_item, "id", item->id);
    cJSON_AddStringToObject(json_item, "name", item->name);
    cJSON_AddNumberToObject(json_item, "quantity", item->quantity);
    cJSON_AddNumberToObject(json_item, "price", item->price);
    return json_item;
}

int main() {
    cJSON* item_list_json = get_store_json();
    ItemList* item_list  = load_items_from_json(item_list_json);
    printf("hello world!\n");
    return 0;
}