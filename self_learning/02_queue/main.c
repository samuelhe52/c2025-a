#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

// Uses mod to wrap around when head is exceeded.

typedef struct {
    int* data;
    int front;
    int rear;
    int capacity;
} Queue;

bool isEmpty(Queue *queue) {
    return queue->front == queue->rear;
}

bool isFull(Queue *queue) {
    // Leave one slot empty to distinguish empty or full
    // Key: queue->rear + 1
    return ((queue->rear + 1) % queue->capacity) == queue->front;
}

Queue* createQueue(int capacity) {
    Queue* queue = malloc(sizeof(Queue));
    queue->data = malloc(capacity * sizeof(int));
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    return queue;
}

void deleteQueue(Queue* queue) {
    free(queue->data);
    free(queue);
}

void enqueue(Queue* queue, const int value) {
    if (isFull(queue)) return;
    queue->data[queue->rear] = value;
    queue->rear = (queue->rear + 1) % queue->capacity;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue)) return -1;
    int value = queue->data[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    return value;
}

int main() {
    Queue* queue1 = createQueue(10);
    Queue* queue2 = createQueue(20);

    for (int i = 0; i < 10; i++) {
        enqueue(queue1, i);
    }
    for (int j = 0; j < 19; j++) {
        enqueue(queue2, j);
    }

    const int a = dequeue(queue1);
    printf("%d\n", a);
    const int b = dequeue(queue1);
    printf("%d\n", b);
    const int c = dequeue(queue1);
    printf("%d\n", c);
    enqueue(queue2, 1000);
    enqueue(queue2, 1001);
    printf("%d\n", dequeue(queue2));

    deleteQueue(queue1);
    deleteQueue(queue2);
    return 0;
}