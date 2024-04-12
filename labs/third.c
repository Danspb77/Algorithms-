#include <stdio.h>
#include <stdlib.h>

// Перечисление для цветов узлов
typedef enum { RED, BLACK } node_color;

// Структура узла красно-черного дерева
typedef struct rb_node {
    int value;               // Значение узла
    node_color color;        // Цвет узла
    struct rb_node *left;    // Левый потомок
    struct rb_node *right;   // Правый потомок
    struct rb_node *parent;  // Родитель
} rb_node;

// Функция для создания нового узла
rb_node* create_rb_node(int value) {
    rb_node *node = malloc(sizeof(rb_node));  // Выделение памяти под узел
    node->value = value;                      // Установка значения узла
    node->color = RED;                        // Новые узлы всегда красные
    node->left = node->right = node->parent = NULL; // Инициализация потомков и родителя
    return node;
}

// Функция для левого поворота дерева относительно заданного узла
void left_rotate(rb_node **root, rb_node *x) {
    rb_node *y = x->right;      // y - правый потомок узла x
    x->right = y->left;         // Перемещаем левое поддерево y к правому поддереву x
    if (y->left != NULL) {
        y->left->parent = x;    // Устанавливаем родителя для левого поддерева y
    }
    y->parent = x->parent;      // Устанавливаем нового родителя для y
    if (x->parent == NULL) {
        *root = y;              // Если x был корнем, y теперь становится корнем
    } else if (x == x->parent->left) {
        x->parent->left = y;    // Если x был левым потомком, y становится левым потомком его родителя
    } else {
        x->parent->right = y;   // Если x был правым потомком, y становится правым потомком его родителя
    }
    y->left = x;                // x становится левым потомком для y
    x->parent = y;              // y становится родителем для x
}

// Функция для правого поворота дерева относительно заданного узла
void right_rotate(rb_node **root, rb_node *x) {
    rb_node *y = x->left;       // y - левый потомок узла x
    x->left = y->right;         // Перемещаем правое поддерево y к левому поддереву x
    if (y->right != NULL) {
        y->right->parent = x;   // Устанавливаем родителя для правого поддерева y
    }
    y->parent = x->parent;      // Устанавливаем нового родителя для y
    if (x->parent == NULL) {
        *root = y;              // Если x был корнем, y теперь становится корнем
    } else if (x == x->parent->right) {
        x->parent->right = y;   // Если x был правым потомком, y становится правым потомком его родителя
    } else {
        x->parent->left = y;    // Если x был левым потомком, y становится левым потомком его родителя
    }
    y->right = x;               // x становится правым потомком для y
    x->parent = y;              // y становится родителем для x
}

// Функция для восстановления свойств красно-черного дерева после вставки узла
void rb_insert_fixup(rb_node **root, rb_node *z) {
    while (z != *root && z->parent->color == RED) { // Пока родитель z красный
        if (z->parent == z->parent->parent->left) { // Если родитель z является левым потомком своего родителя
            rb_node *y = z->parent->parent->right;  // y - дядя z
            if (y && y->color == RED) {             // Если дядя красный
                z->parent->color = BLACK;           // Родитель заменяем на черный
                y->color = BLACK;                   // Дядю заменяем на черный
                z->parent->parent->color = RED;     // Дедушку заменяем на красный
                z = z->parent->parent;              // Переходим к дедушке
            } else {
                if (z == z->parent->right) {        // Если z - правый потомок
                    z = z->parent;                  // Делаем z левым потомком
                    left_rotate(root, z);           // Левый поворот относительно z
                }
                z->parent->color = BLACK;           // Родителя заменяем на черный
                z->parent->parent->color = RED;     // Дедушку заменяем на красный
                right_rotate(root, z->parent->parent); // Правый поворот относительно дедушки
            }
        } else { // Симметричный случай
            rb_node *y = z->parent->parent->left;   // y - дядя z
            if (y && y->color == RED) {             // Если дядя красный
                z->parent->color = BLACK;           // Родитель заменяем на черный
                y->color = BLACK;                   // Дядю заменяем на черный
                z->parent->parent->color = RED;     // Дедушку заменяем на красный
                z = z->parent->parent;              // Переходим к дедушке
            } else {
                if (z == z->parent->left) {         // Если z - левый потомок
                    z = z->parent;                  // Делаем z правым потомком
                    right_rotate(root, z);          // Правый поворот относительно z
                }
                z->parent->color = BLACK;           // Родителя заменяем на черный
                z->parent->parent->color = RED;     // Дедушку заменяем на красный
                left_rotate(root, z->parent->parent); // Левый поворот относительно дедушки
            }
        }
    }
    (*root)->color = BLACK; // Корень всегда черный
}

// Функция для вставки узла в красно-черное дерево
void rb_insert(rb_node **root, rb_node *node) {
    rb_node *y = NULL;          // y - указатель на родителя
    rb_node *x = *root;         // x - текущий узел (начинаем с корня)
    while (x != NULL) {         // Поиск места для вставки нового узла
        y = x;
        if (node->value < x->value) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;           // Устанавливаем родителя для нового узла
    if (y == NULL) {
        *root = node;           // Если дерево пусто, новый узел становится корнем
    } else if (node->value < y->value) {
        y->left = node;         // Если значение нового узла меньше значения родителя, новый узел становится левым потомком
    } else {
        y->right = node;        // Иначе новый узел становится правым потомком
    }
    node->color = RED;         // Новые узлы всегда красные
    rb_insert_fixup(root, node); // Восстановление свойств красно-черного дерева
}

// Функция для прямого обхода красно-черного дерева (в порядке возрастания)
void inorder_traversal(rb_node *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->value);
        inorder_traversal(root->right);
    }
}

// Функция для печати массива
void print_array(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Функция main
int main() {
    rb_node *root = NULL;   // Корень красно-черного дерева
    int values[] = {7, 3, 18, 10, 22, 8, 11, 26}; // Исходный массив значений
    int n = sizeof(values) / sizeof(values[0]);  // Размер массива

    printf("Исходный массив:\n");
    print_array(values, n); // Вывод исходного массива

    // Вставка каждого элемента массива в красно-черное дерево
    for (int i = 0; i < n; i++) {
        rb_insert(&root, create_rb_node(values[i]));
    }

    printf("Отсортированный массив:\n");
    inorder_traversal(root); // Прямой обход красно-черного дерева (в порядке возрастания)
    return 0;
}
