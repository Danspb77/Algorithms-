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

// Вспомогательная функция для разделения массива на две части относительно опорного элемента
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Функция для сортировки массива методом интроспективной сортировки
void introspectiveSort(int arr[], int low, int high, int depth_limit) {
    if (low < high) {
        if (depth_limit == 0) {
            // Если достигнут предел глубины, используем сортировку вставками
            // (для маленьких подмассивов)
            // Можно также использовать любой другой алгоритм сортировки
            // для маленьких подмассивов
            // Например, сортировку пузырьком или сортировку выбором
            for (int i = low + 1; i <= high; i++) {
                int key = arr[i];
                int j = i - 1;
                while (j >= low && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
        } else {
            int pivot = partition(arr, low, high);
            introspectiveSort(arr, low, pivot - 1, depth_limit - 1);
            introspectiveSort(arr, pivot + 1, high, depth_limit - 1);
        }
    }
}

int main() {
    // Пример использования интроспективной сортировки

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

    // Преобразуем элементы в массив для сортировки
    int count = 0;
    current = head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    int arr[count];
    current = head;
    for (int i = 0; i < count; i++) {
        arr[i] = current->data;
        current = current->next;
    }

    // Сортировка
    introspectiveSort(arr, 0, count - 1, 2 * sizeof(int) * 8);

    // Обновляем элементы списка
    current = head;
    for (int i = 0; i < count; i++) {
        current->data = arr[i];
        current = current->next;
    }

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
