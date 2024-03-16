#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STACK_SIZE 1000

// Структура стека
typedef struct {
    int items[STACK_SIZE];
    int top;
} Stack;

// Инициализация стека
void initializeStack(Stack *s) {
    s->top = -1;
}

// Проверка на пустоту стека
bool isEmpty(Stack *s) {
    return s->top == -1;
}

// Помещение элемента на вершину стека
void push(Stack *s, int value) {
    s->items[++s->top] = value;
}

// Извлечение элемента с вершины стека
int pop(Stack *s) {
    return s->items[s->top--];
}

// Функция для разделения массива на две части относительно опорного элемента
int partition(int arr[], int low, int high) {
    int pivot = arr[high]; // Опорный элемент
    int i = low - 1; // Индекс меньшего элемента

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;

    return i + 1;
}

// Функция быстрой сортировки
void quickSort(int arr[], int low, int high) {
    Stack stack;
    initializeStack(&stack);
    push(&stack, low);
    push(&stack, high);

    while (!isEmpty(&stack)) {
        high = pop(&stack);
        low = pop(&stack);

        if (high - low > 10) {
            int pivotIndex = partition(arr, low, high);
            if (pivotIndex - 1 > low) {
                push(&stack, low);
                push(&stack, pivotIndex - 1);
            }
            if (pivotIndex + 1 < high) {
                push(&stack, pivotIndex + 1);
                push(&stack, high);
            }
        } else {
            // Если размер подмассива меньше 10, используем сортировку вставками
            for (int i = low + 1; i <= high; i++) {
                int key = arr[i];
                int j = i - 1;
                while (j >= low && arr[j] > key) {
                    arr[j + 1] = arr[j];
                    j--;
                }
                arr[j + 1] = key;
            }
        }
    }
}

// Пример использования
int main() {
    int arr[] = {9, 4, 2, 7, 5, 1, 8, 3, 6, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Исходный массив:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    quickSort(arr, 0, n - 1);

    printf("Отсортированный массив:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}
