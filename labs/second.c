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
// Функция для получения вершины стека без удаления
int peek(Stack *s) {
    if (isEmpty(s)) {
        printf("Ошибка: Стек пуст.\n");
        exit(EXIT_FAILURE);
    }
    return s->top->data;
}

int partition(Stack *stack, int low, int high) {
    int pivot = pop(stack); // Получаем опорный элемент из вершины стека
    int i = low - 1; // Индекс меньшего элемента

    // Проходим по диапазону и переносим элементы, меньшие или равные опорному, влево
    for (int j = low; j < high; j++) {
        int current = pop(stack);
        if (current <= pivot) {
            i++;
            push(stack, current);
        }
    }

    // Помещаем опорный элемент в его окончательную позицию
    push(stack, pop(stack)); // Перемещаем найденный pivot в конец массива
    push(stack, pivot); // Возвращаем pivot в стек
    return i + 1;
}

// Функция быстрой сортировки с использованием стека
void quickSort(Stack *stack, int low, int high) {
    push(stack, low);
    push(stack, high);

    while (!isEmpty(stack)) {
        high = pop(stack);
        low = pop(stack);

        if (high - low > 10) {
            int pivotIndex = partition(stack, low, high);
            if (pivotIndex - 1 > low) {
                push(stack, low);
                push(stack, pivotIndex - 1);
            }
            if (pivotIndex + 1 < high) {
                push(stack, pivotIndex + 1);
                push(stack, high);
            }
        } else {
            // Если размер кусочка данных меньше 10, используем сортировку вставками
            for (int i = low + 1; i <= high; i++) {
                int key = pop(stack);
                int j = i - 1;
                while (j >= low && peek(stack) > key) {
                    push(stack, pop(stack));
                    j--;
                }
                push(stack, key);
            }
        }
    }
}

int main() {
    Stack stack;
    initializeStack(&stack);

    // Создаем исходные данные
    int arr[] = {9, 4, 2, 7, 5, 1, 8, 3, 6, 0};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Исходные данные:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
        push(&stack, arr[i]); // Добавляем элементы массива в стек
    }
    printf("\n");

    // Сортируем данные в стеке
    quickSort(&stack, 0, n - 1);

    // Выводим отсортированные данные из стека
    printf("Отсортированные данные:\n");
    while (!isEmpty(&stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

    return 0;
}
