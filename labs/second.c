#include <stdio.h>
#include <stdlib.h>

// Определение структуры для элемента двусвязного списка
struct Node {
    int data;           // Значение элемента
    struct Node* prev;  // Указатель на предыдущий элемент
    struct Node* next;  // Указатель на следующий элемент
};

// Функция для создания нового элемента списка
struct Node* newNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления элемента в конец списка
void enqueue(struct Node** head, struct Node** tail, int data) {
    struct Node* new_node = newNode(data);
    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        (*tail)->next = new_node;
        new_node->prev = *tail;
        *tail = new_node;
    }
}

// Функция для удаления элемента из начала списка
int dequeue(struct Node** head, struct Node** tail) {
    if (*head == NULL)
        return -1; // Очередь пуста
    int data = (*head)->data;
    struct Node* temp = *head;
    if (*head == *tail) {
        *head = NULL;
        *tail = NULL;
    } else {
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
    free(temp);
    return data;
}

// Функция для проверки, пуста ли очередь
int isEmpty(struct Node* head) {
    return head == NULL;
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
void introspectiveSortList(struct Node* head, struct Node* tail, int depth_limit) {
    if (head != NULL && tail != NULL && head != tail && depth_limit > 0) {
        struct Node* pivot = partition(head, tail);
        introspectiveSortList(head, pivot->prev, depth_limit - 1);
        introspectiveSortList(pivot->next, tail, depth_limit - 1);
    }
}

int main() {
    // Пример использования интроспективной сортировки для списка

    struct Node* head = NULL;
    struct Node* tail = NULL;

    enqueue(&head, &tail, 5);
    enqueue(&head, &tail, 3);
    enqueue(&head, &tail, 8);
    enqueue(&head, &tail, 2);
    enqueue(&head, &tail, 7);

    printf("Before sorting:\n");
    struct Node* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }

    // Сортировка списка
    introspectiveSortList(head, tail, 2 * sizeof(int) * 8);

    printf("\nAfter sorting:\n");
    current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }

    // Очистка памяти
    current = head;
    while (current != NULL) {
        struct Node* temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}
