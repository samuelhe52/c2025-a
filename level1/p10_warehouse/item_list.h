#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEM_NAME_LEN 50

typedef struct {
    int id;
    char name[MAX_ITEM_NAME_LEN];
    int quantity;
    double price;
} Item;

typedef struct ItemNode {
    Item item;
    struct ItemNode* next;
} ItemNode;

typedef struct {
    ItemNode* head;
    int count;
} ItemList;

// Initialize an empty item list
ItemList* item_list_create(void);

// Add an item to the list
void item_list_add(ItemList* list, const Item* item);

// Remove an item by ID
int item_list_remove_by_id(ItemList* list, int id);

// Find an item by ID
Item* item_list_find_by_id(ItemList* list, int id);

// Get the count of items in the list
int item_list_get_count(const ItemList* list);

// Print all items in the list
void item_list_print(const ItemList* list);

// Free all memory used by the list
void item_list_destroy(ItemList* list);

// Create an item with given parameters
Item* create_item(int id, const char* name, int quantity, double price);

// Print a single item
void print_item(const Item* item);

#endif // ITEM_LIST_H
