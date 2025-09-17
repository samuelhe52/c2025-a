#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int* data;
    int top_idx;
    int capacity;
} Stack;

Stack* init_stack(int capacity) {
    Stack* stack = malloc(sizeof(Stack));
    stack->data = malloc(sizeof(int) * capacity);
    stack->top_idx = -1;
    stack->capacity = capacity;
    return stack;
}

void delete_stack(Stack* stack) {
    free(stack->data);
    free(stack);
}

int pop(Stack *s) {
    if (s->top_idx < 0) {
        perror("Stack empty");
        return -1;
    }
    return s->data[s->top_idx--];
}

void push(Stack* s, int n) {
    if (s->top_idx > s->capacity - 1) {
        perror("Stack full");
        exit(1);
    }
    s->data[++s->top_idx] = n;
}

void print_top(Stack* s) {
    printf("%d\n", s->data[s->top_idx]);
}

int get_top(Stack* s) {
    return s->data[s->top_idx];
}

void swap_top_two(Stack* s) {
    if (s->top_idx < 2) {
        perror("Not enough elements");
        return;
    }
    const int topmost = pop(s);
    const int second_topmost = pop(s);
    push(s, topmost);
    push(s, second_topmost);
}

void clear_stack(Stack* s) {
    s->top_idx = 0;
}

int main() {
    Stack* stack = init_stack(MAX);
    if (stack == NULL) {
        perror("Stack initialization failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < MAX; i++) {
        push(stack, i);
    }

    print_top(stack);
    printf("Popped element: %d\n", pop(stack));

    push(stack, 1000);
    print_top(stack);

    swap_top_two(stack);
    print_top(stack);

    printf("The topmost element is now: %d\n", get_top(stack));
    clear_stack(stack);
    printf("The current topmost element after clearing the stack is: %d\n", get_top(stack));

    delete_stack(stack);
    return 0;
}