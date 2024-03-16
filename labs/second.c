// Данные строки подключают необходимые библиотеки для работы с стандартным вводом/выводом, 
// выделением памяти и булевыми значениями.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Определение структуры узла списка
// Здесь определена структура Node, представляющая узел односвязного списка. 
// Она содержит поле data для хранения значения и указатель next, указывающий на следующий узел в списке.
typedef struct Node {
    int data;           // Значение узла
    struct Node* next;  // Указатель на следующий узел
} Node;

// Определение структуры стека
typedef struct {
    Node* top;  // Указатель на вершину стека
} Stack;

// Инициализация стека
void initializeStack(Stack *s) {
    s->top = NULL;  // Устанавливаем указатель на вершину стека в NULL (пустой стек)
}

// Проверка на пустоту стека
bool isEmpty(Stack *s) {
    return s->top == NULL;  // Стек пуст, если указатель на вершину равен NULL
}

// Помещение элемента на вершину стека
void push(Stack *s, int value) {
    // Создаем новый узел
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Ошибка: Не удалось выделить память для нового узла.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;  // Устанавливаем значение нового узла
    newNode->next = s->top; // Новый узел указывает на предыдущую вершину стека
    s->top = newNode;       // Переносим указатель на вершину стека на новый узел
}

// Извлечение элемента с вершины стека
int pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Ошибка: Стек пуст.\n");
        exit(EXIT_FAILURE);
    }
    // Получаем значение вершины стека
    int value = s->top->data;
    // Удаляем вершину стека и освобождаем память
    Node* temp = s->top;
    s->top = s->top->next;
    free(temp);
    return value;
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

// Функция быстрой сортировки с использованием стека
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
