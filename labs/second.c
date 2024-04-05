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
    // Выделение памяти под новый узел
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    // Инициализация данных нового узла
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Функция для добавления элемента в конец списка
void enqueue(struct Node** head, struct Node** tail, int data) {
    // Создание нового узла
    struct Node* new_node = newNode(data);
    // Если список пустой
    if (*head == NULL) {
        *head = new_node;
        *tail = new_node;
    } else {
        // Добавление узла в конец списка
        (*tail)->next = new_node;
        new_node->prev = *tail;
        *tail = new_node;
    }
}

// Функция для удаления элемента из начала списка
int dequeue(struct Node** head, struct Node** tail) {
    // Если список пустой
    if (*head == NULL)
        return -1; // Очередь пуста
    // Получение данных первого узла
    int data = (*head)->data;
    struct Node* temp = *head;
    // Если в списке один узел
    if (*head == *tail) {
        *head = NULL;
        *tail = NULL;
    } else {
        // Удаление первого узла из списка
        *head = (*head)->next;
        (*head)->prev = NULL;
    }
    // Освобождение памяти удаленного узла
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
    // Если список пустой или содержит только один элемент
    if (head == NULL || tail == NULL)
        return NULL;

    int pivot = tail->data;
    struct Node* i = head->prev;

    // Перебор элементов списка
    for (struct Node* j = head; j != tail; j = j->next) {
        // Если текущий элемент меньше опорного
        if (j->data < pivot) {
            // Увеличение i и обмен значениями i и j
            i = (i == NULL) ? head : i->next;
            swap(&(i->data), &(j->data));
        }
    }
    // Увеличение i и обмен значениями i и опорного элемента
    i = (i == NULL) ? head : i->next;
    swap(&(i->data), &(tail->data));
    return i;
}

// Функция для сортировки списка методом интроспективной сортировки
void introspectiveSortList(struct Node* head, struct Node* tail, int depth_limit) {
    // Если список не пустой и есть глубина рекурсии
    if (head != NULL && tail != NULL && head != tail && depth_limit > 0) {
        // Разделение списка и сортировка каждой части
        struct Node* pivot = partition(head, tail);
        introspectiveSortList(head, pivot->prev, depth_limit - 1);
        introspectiveSortList(pivot->next, tail, depth_limit - 1);
    }
}

int main() {
    // Пример использования интроспективной сортировки для списка

    struct Node* head = NULL;
    struct Node* tail = NULL;

    // Добавление элементов в список
    enqueue(&head, &tail, 5);
    enqueue(&head, &tail, 3);
    enqueue(&head, &tail, 8);
    enqueue(&head, &tail, 2);
    enqueue(&head, &tail, 7);

    printf("Before sorting:\n");
    // Вывод элементов списка до сортировки
    struct Node* current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }

    // Сортировка списка
    introspectiveSortList(head, tail, 2 * sizeof(int) * 8);

    printf("\nAfter sorting:\n");
    // Вывод элементов списка после сортировки
    current = head;
    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }

    // Очистка памяти от списка
    current = head; // Устанавливаем указатель на начало списка
    while (current != NULL) { // Пока не достигнут конец списка
        struct Node* temp = current; // Сохраняем текущий узел во временную переменную
        current = current->next; // Переходим к следующему узлу списка
        free(temp); // Освобождаем память, занимаемую текущим узлом
    }


    return 0;
}
