#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* start;
    Node* end;
} Queue;

Queue* createQueue();
void enqueue(Queue* queue, char value);
char dequeue(Queue* queue);
void filterQueue(Queue* queue);
void deleteElements(Queue* queue, int number);
void printQueue(Queue* queue);

int main() {
    Queue* queue = createQueue();

    char elements[] = {'A', 'B', 'C', 'D', 'E', 'E', 'D', 'C', 'B', 'A'};

    int arrLength = sizeof(elements) / sizeof(elements[0]);

    for (int i = 0; i < arrLength; i++) {
        enqueue(queue, elements[i]);
    }

    printQueue(queue);

    filterQueue(queue);

    printQueue(queue);

    deleteElements(queue, 3);

    printQueue(queue);

    return 0;
}

Queue* createQueue() {
    Queue* queue = malloc(sizeof(Queue));

    queue->start = NULL;
    queue->end = NULL;

    return queue;
}

void enqueue(Queue* queue, char value) {
    Node* newNode = malloc(sizeof(Node));

    newNode->data = value;
    newNode->next = NULL;

    if (queue->end == NULL) {
        queue->start = newNode;
        queue->end = newNode;
    } else {
        queue->end->next = newNode;
        queue->end = newNode;
    }
}

char dequeue(Queue* queue) {
    if (queue->start == NULL) {
        return '\0';
    }

    Node* temp = queue->start;
    char value = temp->data;
    queue->start = queue->start->next;

    if (queue->start == NULL) {
        queue->end = NULL;
    }

    free(temp);

    return value;
}

void filterQueue(Queue* queue) {
    Node* current = queue->start;
    Node* prev = NULL;

    while (current != NULL && current->next != NULL) {
        if (current->data < current->next->data) {
            while (current->next != NULL && current->data < current->next->data) {
                current = current->next;
            }

            Node* end = current->next;

            if (prev == NULL) {
                queue->start = end;
            } else {
                prev->next = end;
            }

            current = end;
        } else {
            prev = current;
            current = current->next;
        }
    }

    if (queue->start == NULL) {
        queue->end = NULL;
    }
}

void deleteElements(Queue* queue, int number) {
    for (int i = 0; i < number; i++) {
        if (dequeue(queue) == '\0') {
            break;
        }
    }
}

void printQueue(Queue* queue) {
    Node* current = queue->start;

    while (current != NULL) {
        printf("%c -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}