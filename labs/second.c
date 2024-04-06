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
    // Проверяем, пуста ли очередь
    if (isEmpty(queue))
        return -1; // Возвращаем -1, если очередь пуста

    int data = queue->front->data; // Получаем данные первого элемента

    // Если в очереди только один элемент
    if (queue->front == queue->rear) {
        free(queue->front); // Освобождаем память, занимаемую первым элементом
        queue->front = NULL; // Обнуляем указатель на первый элемент
        queue->rear = NULL; // Обнуляем указатель на последний элемент
    } else {
        // Если в очереди больше одного элемента
        struct Node* temp = queue->front; // Временный указатель на первый элемент
        queue->front = queue->front->next; // Перемещаем указатель на первый элемент на следующий элемент
        queue->front->prev = queue->rear; // Устанавливаем указатель на предыдущий элемент первого элемента на последний элемент
        queue->rear->next = queue->front; // Устанавливаем указатель на следующий элемент последнего элемента на первый элемент
        free(temp); // Освобождаем память, занимаемую первым элементом
    }
    return data; // Возвращаем данные удаленного элемента
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
    struct Queue* queue = createQueue();

    FILE* file = fopen("file2.txt", "r"); // Открытие файла для чтения
    if (file == NULL) {
        printf("Failed to open the file.\n");
        return -1;
    }

    int num;
    while (fscanf(file, "%d", &num) != EOF) { // Считывание чисел из файла
        enqueue(queue, num); // Добавление считанного числа в очередь
    }

    fclose(file); // Закрытие файла

    printf("Before sorting: ");
    printQueue(queue);

    introspectiveSort(queue);

    printf("After sorting: ");
    printQueue(queue);

    while (!isEmpty(queue)) {
        dequeue(queue);
    }

    free(queue);

    return 0;
}