#include "store_json_management.h"

bool is_store_file_empty() {
    FILE* file = fopen(WAREHOUSE_STORE_FILE, "r");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fclose(file);
    return size == 0;
}

void initialize_store_file() {
    FILE* file = fopen(WAREHOUSE_STORE_FILE, "w");
    if (file == NULL) {
        perror("Error creating store file");
        exit(EXIT_FAILURE);
    }

    cJSON* json_root = cJSON_CreateObject();
    char* json_string = cJSON_Print(json_root);

    fputs(json_string, file);
    fputc('\n', file);

    free(json_string);
    cJSON_Delete(json_root);
    fclose(file);
}

char* read_file_to_string(const char* filename) {
    FILE* file = NULL;
    long file_size = 0;
    char* buffer = NULL;

    file = fopen(filename, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    buffer = (char*)malloc(file_size + 1);
    if (buffer == NULL) {
        perror("Error allocating memory");
        fclose(file);
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, file_size, file);

    buffer[file_size] = '\0';
    fclose(file);
    return buffer;
}

cJSON* get_store_json() {
    char* json_string = read_file_to_string(WAREHOUSE_STORE_FILE);
    cJSON* json = cJSON_Parse(json_string);

    free(json_string);
    return json;
}

ItemList* load_items_from_json(const cJSON* json) {
    const cJSON* json_item = NULL;
    ItemList* list = item_list_create();

    if (!cJSON_IsObject(json)) {
        perror("Error parsing JSON: \"items\" is not object");
        exit(EXIT_FAILURE);
    }

    cJSON_ArrayForEach(json_item, json) {
        const cJSON* name = cJSON_GetObjectItemCaseSensitive(json_item, "name");
        const cJSON* quantity = cJSON_GetObjectItemCaseSensitive(json_item, "quantity");
        const cJSON* price = cJSON_GetObjectItemCaseSensitive(json_item, "price");

        const Item* item = create_item(name->valuestring, quantity->valueint, price->valuedouble);
        item_list_add(list, item);
    }

    return list;
}

cJSON* save_list_to_json_object(const ItemList* list) {
    cJSON* json_root = cJSON_CreateObject();
    const ItemNode* current = list->head;
    while (current != NULL) {
        cJSON* json_item = create_json_item(&(current->item));
        cJSON_AddItemToObject(json_root, current->item.name, json_item);
        current = current->next;
    }

    return json_root;
}

void save_object_to_store_file(const cJSON* json) {
    char* json_string = cJSON_Print(json);
    FILE* file = fopen(WAREHOUSE_STORE_FILE, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        exit(EXIT_FAILURE);
    }
    fputs(json_string, file);
    fputc('\n', file);
    fclose(file);
    free(json_string);
}

int json_get_item_count(const cJSON* json) {
    if (!cJSON_IsObject(json)) {
        perror("Error parsing JSON: \"items\" is not object");
        exit(EXIT_FAILURE);
    }
    return cJSON_GetArraySize(json);
}

cJSON* create_json_item(const Item* item) {
    cJSON* json_item = cJSON_CreateObject();
    cJSON_AddStringToObject(json_item, "name", item->name);
    cJSON_AddNumberToObject(json_item, "quantity", item->quantity);
    cJSON_AddNumberToObject(json_item, "price", item->price);
    return json_item;
}