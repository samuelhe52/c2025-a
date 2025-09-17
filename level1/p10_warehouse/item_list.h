#pragma once

#ifndef ITEM_LIST_H
#define ITEM_LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ITEM_NAME_MAX_LEN 50
#define MAX_JSON_SIZE 1048576
#define MAX_ITEM_COUNT 1000

// Represent an item in the warehouse.
typedef struct {
    char name[ITEM_NAME_MAX_LEN];
    int quantity;
    double price;
} Item;

// Use linked list to store items
typedef struct ItemNode {
    Item item;
    struct ItemNode* next;
} ItemNode;

// Database representation
typedef struct {
    ItemNode* head;
    int count;
} ItemList;

// Initialize an empty item list
ItemList* item_list_create(void);

// Add an item to the list
void item_list_add(ItemList* list, const Item* item);

// Remove an item by name
int item_list_remove_by_name(ItemList* list, const char* name);

// Find an item by name
Item* item_list_find_by_name(ItemList* list, const char* name);

// Get the count of items in the list
int item_list_get_count(const ItemList* list);

// Print all items in the list
void item_list_print(const ItemList* list);

// Free all memory used by the list
void item_list_destroy(ItemList* list);

// Create an item with given parameters
Item* create_item(const char* name, int quantity, double price);

// Print a single item
void print_item(const Item* item);

#endif // ITEM_LIST_H
