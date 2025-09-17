#include "item_list.h"

ItemList* item_list_create(void) {
    ItemList* list = malloc(sizeof(ItemList));
    if (list == NULL) {
        perror("Failed to allocate memory for ItemList");
        exit(EXIT_FAILURE);
    }
    list->head = NULL;
    list->count = 0;
    return list;
}

void item_list_add(ItemList* list, const Item* item) {
    ItemNode* new_node = malloc(sizeof(ItemNode));
    if (new_node == NULL) {
        perror("Failed to allocate memory for ItemNode");
        exit(EXIT_FAILURE);
    }

    new_node->item = *item;
    new_node->next = list->head;
    list->head = new_node;
    list->count++;
}

int item_list_remove_by_name(ItemList* list, const char* name) {
    ItemNode* current = list->head;
    ItemNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            if (prev == NULL) {
                // Removing the first node
                list->head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            list->count--;
            return 1; // Success
        }
        prev = current;
        current = current->next;
    }
    return 0; // Item not found
}

Item* item_list_find_by_name(ItemList* list, const char* name) {
    ItemNode* current = list->head;

    while (current != NULL) {
        if (strcmp(current->item.name, name) == 0) {
            return &(current->item);
        }
        current = current->next;
    }
    return NULL; // Item not found
}

int item_list_get_count(const ItemList* list) {
    return list->count;
}

void item_list_print(const ItemList* list) {
    ItemNode* current = list->head;
    printf("Total items: %d\n", list->count);

    while (current != NULL) {
        print_item(&(current->item));
        current = current->next;
    }
}

void item_list_destroy(ItemList* list) {
    ItemNode* current = list->head;
    ItemNode* temp;

    while (current != NULL) {
        temp = current;
        current = current->next;
        free(temp);
    }

    free(list);
}

Item* create_item(const char* name, int quantity, double price) {
    Item* item = malloc(sizeof(Item));
    if (item == NULL) {
        perror("Failed to allocate memory for Item");
        exit(EXIT_FAILURE);
    }

    strncpy(item->name, name, ITEM_NAME_MAX_LEN - 1);
    item->name[ITEM_NAME_MAX_LEN - 1] = '\0'; // Ensure null termination
    item->quantity = quantity;
    item->price = price;
    return item;
}

void print_item(const Item* item) {
    printf("Item name: %s, quantity: %d, price: %.2f\n",
           item->name, item->quantity, item->price);
}
