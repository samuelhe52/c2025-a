#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node* next;
} Node;

Node* initialize_list(const int n) {
    Node* head = (Node*)malloc(sizeof(Node));
    head->data = n;
    head->next = NULL;
    return head;
}

void insert_before_head(Node** head_ref, const int n) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = n;
    new_node->next = (*head_ref);
    *head_ref = new_node;
}

void insert_after_head(Node* head, const int n) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = n;
    new_node->next = head->next;
    head->next = new_node;
}

void append_list(Node* head, const int n) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    new_node->data = n;
    new_node->next = NULL;

    Node* tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    tail->next = new_node;
}

void delete_element(Node** head, const int n) {
    Node* prev = NULL;
    Node* current = *head;

    if (*head == NULL) return;
    if ((*head)->data == n) {
        *head = (*head)->next;
        free(current);
        return;
    }

    while (current != NULL) {
        prev = current;
        current = current->next;
        if (current->data == n) {
            prev->next = current->next;
            free(current);
            return;
        }
    }
}

void reverse_list(Node** head_ref) {
    Node* prev = NULL;
    Node* current = *head_ref;
    Node* temp = NULL;

    while (current != NULL) {
        temp = current->next;
        current->next = prev;
        prev = current;
        current = temp;
    }

    *head_ref = prev;
}

// Initialize the linked list with 0-10
Node* create_linked_list() {
    Node *head = NULL;
    Node *tail = NULL;

    for (int i = 0; i < 10; i++) {
        Node *new_node = (Node*)malloc(sizeof(Node));
        if (new_node == NULL) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }
        new_node->data = i;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
            tail = new_node;
        }

        if (tail != NULL) {
            tail->next = new_node; // extend the list
            tail = tail->next; // move tail forward
        }
    }

    return head;
}

void print_linked_list(const Node* node) {
    while (node != NULL) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void reverse_linked_list(Node** head_ref) {
    Node* prev = NULL;
    Node* current = *head_ref;
    Node* temp = NULL;

    while (current != NULL) {
        temp = current->next; // stores the next node before breaking the link
        current->next = prev; // reverse the link's direction

        // The current link has been reversed
        // move prev and current forward to reverse the next link
        prev = current;
        current = temp;
    }

    // Update head to the new head node (originally the last node)
    *head_ref = prev;
}

int find_5_in_list(const Node* head) {
    const Node* tail = head;

    int idx = 0;
    while (tail != NULL) {
        if (tail->data == 5) {
            return idx;
        }
        idx++;
        tail = tail->next;
    }

    return -1;
}

int find_second_5_in_list(const Node* head) {
    const Node* tail = head;

    int idx = 0;
    int counter = 0;
    while (tail != NULL) {
        if (tail->data == 5) {
            if (++counter == 2) {
                return idx;
            }
        }
        idx++;
        tail = tail->next;
    }

    return -1;
}

void append_to_list(Node* head, const int data) {
    Node* tail = head;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    new_node->data = data;
    new_node->next = NULL;

    while (tail->next != NULL) {
        tail = tail->next;
    }
    tail->next = new_node;
}

int main() {
    Node *head = create_linked_list();
    print_linked_list(head);
    reverse_linked_list(&head);
    print_linked_list(head);
    reverse_linked_list(&head);

    Node* another_list_head = create_linked_list();
    Node* last = head;

    while (last->next != NULL) {
        last = last->next;
    }
    last->next = another_list_head;

    print_linked_list(head);

    const int pos = find_5_in_list(head);
    printf("5 is at index %d\n", pos);

    const int second_pos = find_second_5_in_list(head);
    printf("Second 5 is at index %d\n", second_pos);

    free(head);
    return 0;
}