#include <stdio.h>
#include <stdlib.h>

// Определение структуры для элемента двусвязного списка
struct Node {
    int data;           // Значение элемента
    struct Node* prev;  // Указатель на предыдущий элемент
    struct Node* next;  // Указатель на следующий элемент
};

// Определение структуры для кольцевой очереди на базе двусвязного списка
struct Queue {
    struct Node* front;  // Указатель на первый элемент
    struct Node* rear;   // Указатель на последний элемент
};

// Функция для создания нового элемента списка
struct Node* newNode(int data) {
    // Выделение памяти под новый узел
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // Инициализация данных нового узла
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Функция для инициализации кольцевой очереди
struct Queue* createQueue() {
    // Выделение памяти под новую очередь
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    // Инициализация указателей на начало и конец очереди
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Функция для добавления элемента в конец кольцевой очереди
void enqueue(struct Queue* queue, int data) {
    // Создание нового узла
    struct Node* new_node = newNode(data);
    // Если очередь пустая
    if (queue->rear == NULL) {
        queue->front = new_node;
        queue->rear = new_node;
        queue->rear->next = queue->front;
        queue->front->prev = queue->rear;
    } else {
        // Добавление узла в конец очереди
        new_node->prev = queue->rear;
        new_node->next = queue->front;
        queue->rear->next = new_node;
        queue->rear = new_node;
        queue->front->prev = queue->rear;
    }
}

// Функция для удаления и возврата первого элемента из кольцевой очереди
int dequeue(struct Queue* queue) {
    // Если очередь пустая
    if (queue->front == NULL)
        return -1; // Очередь пуста, возвращаем -1
    int data = queue->front->data;
    if (queue->front == queue->rear) {
        // Если в очереди был один элемент
        free(queue->front);
        queue->front = NULL;
        queue->rear = NULL;
    } else {
        // Если в очереди было больше одного элемента
        struct Node* temp = queue->front;
        queue->front = queue->front->next;
        queue->front->prev = queue->rear;
        queue->rear->next = queue->front;
        free(temp);
    }
    return data;
}

// Функция для проверки, пуста ли кольцевая очередь
int isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}

// Функция для обмена значениями
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Функция для разделения списка на две части относительно опорного элемента
struct Node* partition(struct Node* head, struct Node* tail) {
    if (head == NULL || tail == NULL)
        return NULL;

    int pivot = tail->data;
    struct Node* i = head->prev;

    for (struct Node* j = head; j != tail; j = j->next) {
        if (j->data < pivot) {
            i = (i == NULL) ? head : i->next;
            swap(&(i->data), &(j->data));
        }
    }
    i = (i == NULL) ? head : i->next;
    swap(&(i->data), &(tail->data));
    return i;
}

// Функция для сортировки списка методом интроспективной сортировки
void introspectiveSort(struct Queue* queue) {
    // Если очередь пуста или содержит только один элемент, завершаем сортировку
    if (isEmpty(queue) || queue->front->next == queue->front)
        return;

    struct Node* head = queue->front;
    struct Node* tail = queue->rear;
    struct Node* pivot = partition(head, tail);

    struct Queue* leftQueue = createQueue();
    struct Queue* rightQueue = createQueue();

    struct Node* current = head;
    while (current != pivot) {
        enqueue(leftQueue, current->data);
        current = current->next;
    }

    current = pivot->next;
    while (current != head) {
        enqueue(rightQueue, current->data);
        current = current->next;
    }

    introspectiveSort(leftQueue);
    introspectiveSort(rightQueue);

    current = head;
    while (!isEmpty(leftQueue)) {
        current->data = dequeue(leftQueue);
        current = current->next;
    }

    current = pivot->next;
    while (!isEmpty(rightQueue)) {
        current->data = dequeue(rightQueue);
        current = current->next;
    }

    free(leftQueue);
    free(rightQueue);
}

// Функция для вывода содержимого кольцевой очереди
void printQueue(struct Queue* queue) {
    if (isEmpty(queue))
        printf("Queue is empty\n");
    else {
        struct Node* current = queue->front;
        do {
            printf("%d ", current->data);
            current = current->next;
        } while (current != queue->front);
        printf("\n");
    }
}

int main() {
    // Пример использования интроспективной сортировки для кольцевой очереди

    struct Queue* queue = createQueue();

    enqueue(queue, 5);
    enqueue(queue, 3);
    enqueue(queue, 8);
    enqueue(queue, 2);
    enqueue(queue, 7);

    printf("Before sorting: ");
    printQueue(queue);

    introspectiveSort(queue);

    printf("After sorting: ");
    printQueue(queue);

    // Очистка памяти
    while (!isEmpty(queue)) {
        dequeue(queue);
    }

    free(queue);

    return 0;
}
