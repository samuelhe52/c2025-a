#include <printf.h>
#include "store_json_management.h"
#include "item_list.h"

void clear_console();
void print_menu();
void process_print_list_items(ItemList* item_list);
void process_stock_in(ItemList* item_list);
void process_stock_out(ItemList* item_list);
void process_exit(ItemList* item_list);

void clear_console() {
    system("clear");
}

void print_menu() {
    printf("\n");
    printf("================= Warehouse Management ================\n");
    printf("Select an option from the menu (1-4):\n");
    printf("1. Show item list\n");
    printf("2. Stock in\n");
    printf("3. Stock out\n");
    printf("4. Save and exit\n");
}

void process_print_list_items(ItemList* item_list) {
    clear_console();
    item_list_print(item_list);
    printf("\nPress 'q' to go back to the root menu.\n");
    while (getchar() != 'q'); // wait for q to exit
}

void process_stock_in(ItemList* item_list) {
    clear_console();
    // Stock in
    int quantity;
    double price;
    char stock_in_name[ITEM_NAME_MAX_LEN];
    printf("Enter item name: ");
    fgets(stock_in_name, sizeof(stock_in_name), stdin);
    stock_in_name[strcspn(stock_in_name, "\n")] = '\0';
    printf("Enter item quantity: ");
    scanf("%d", &quantity);
    printf("Enter item price: ");
    scanf("%lf", &price);

    Item* existing_item = item_list_find_by_name(item_list, stock_in_name);
    if (existing_item != NULL) {
        printf("Found existing item with name: %s\n", stock_in_name);
        existing_item->quantity += quantity;
        existing_item->price = price; // Update price to the latest
        printf("Item updated: ");
        print_item(existing_item);
    } else {
        printf("Item not found, adding new item\n");
        const Item* new_item = create_item(stock_in_name, quantity, price);
        item_list_add(item_list, new_item);
        printf("Item added: ");
        print_item(new_item);
    }
    printf("\nPress 'q' to go back to the root menu.\n");
    while (getchar() != 'q'); // wait for q to exit
}

void process_stock_out(ItemList* item_list) {
    clear_console();
    // Stock out
    char stock_out_name[ITEM_NAME_MAX_LEN];
    int stock_out_quantity;
    printf("Enter item name: ");
    scanf("%[^\n]", stock_out_name);
    printf("Enter stock out quantity: ");
    scanf("%d", &stock_out_quantity);

    Item* item_to_stock_out = item_list_find_by_name(item_list, stock_out_name);
    if (item_to_stock_out != NULL) {
        if (item_to_stock_out->quantity - stock_out_quantity > 0) {
            item_to_stock_out->quantity -= stock_out_quantity;
            printf("Item %s stocked out. Remaining quantity: %d\n", stock_out_name, item_to_stock_out->quantity);
        } else if (item_to_stock_out->quantity - stock_out_quantity == 0) {
            item_list_remove_by_name(item_list, stock_out_name);
            printf("Item %s has been completely stocked out and removed from the warehouse.\n", stock_out_name);
        } else {
            printf("Invalid stock out quantity. Only %d of item \"%s\" remains.\n", item_to_stock_out->quantity, stock_out_name);
            printf("No changes were made.\n");
        }
    } else {
        printf("Item with name %s not found.\n", stock_out_name);
    }
    printf("\nPress 'q' to go back to the root menu.\n");
    while (getchar() != 'q'); // wait for q to exit
}

void process_exit(ItemList* item_list) {
    clear_console();
    // Save the current list to file and exit.
    cJSON* json_list = save_list_to_json_object(item_list);
    save_object_to_store_file(json_list);
    item_list_destroy(item_list);
}

int main() {
    ItemList* item_list;
    if (!is_store_file_empty()) {
        cJSON* item_list_json = get_store_json();
        item_list  = load_items_from_json(item_list_json);
    } else {
        initialize_store_file();
        item_list = item_list_create();
    }

    int option = 0;
    int exit = false;
    while (!exit) {
        print_menu();
        char buffer[4];
        if (fgets(buffer, sizeof(buffer), stdin)) {
            option = (int)strtol(buffer, NULL, 10);
        }
        switch (option) {
            case 1:
                process_print_list_items(item_list);
                clear_console();
                break;
            case 2:
                process_stock_in(item_list);
                clear_console();
                break;
            case 3:
                process_stock_out(item_list);
                clear_console();
                break;
            case 4:
                process_exit(item_list);
                exit = true;
                break;
            default:
                printf("Invalid option. Please select an option from 1 to 4.\n");
                option = 0;
                break;
        }
    }

    return 0;
}