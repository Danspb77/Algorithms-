#include <stdio.h>
#include <stdlib.h>

// Структура узла красно-черного дерева
typedef struct rb_node {
    int data;
    struct rb_node *parent;
    struct rb_node *left;
    struct rb_node *right;
    int color; // 0 - черный, 1 - красный
} RBNode;

// Структура для красно-черного дерева
typedef struct rb_tree {
    RBNode *root;
} RBTree;

// Создание нового узла
RBNode* createNode(int data);


// Создание нового узла
RBNode* createNode(int data) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    if (newNode == NULL) {
        printf("Ошибка: Не удалось выделить память для узла\n");
        exit(1);
    }
    newNode->data = data;
    newNode->parent = NULL;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->color = 1; // Новые узлы всегда красные
    return newNode;
}

// Вставка узла в красно-черное дерево
void insertRBNode(RBTree *tree, int data) {
    RBNode *newNode = createNode(data);
    RBNode *parent = NULL;
    RBNode *current = tree->root;

    // Находим место для вставки нового узла
    while (current != NULL) {
        parent = current;
        if (data < current->data) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    newNode->parent = parent;
    if (parent == NULL) {
        // Если дерево было пусто
        tree->root = newNode;
    } else if (data < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }

    // Выполняем восстановление свойств красно-черного дерева
    // (поддержание красно-черных свойств)
    // Доработка этой части
    RBNode *uncle;
    while (newNode != tree->root && newNode->parent->color == 1) {
        if (newNode->parent == newNode->parent->parent->left) {
            uncle = newNode->parent->parent->right;
            if (uncle != NULL && uncle->color == 1) {
                newNode->parent->color = 0;
                uncle->color = 0;
                newNode->parent->parent->color = 1;
                newNode = newNode->parent->parent;
            } else {
                if (newNode == newNode->parent->right) {
                    newNode = newNode->parent;
                    rotateLeft(tree, newNode);
                }
                newNode->parent->color = 0;
                newNode->parent->parent->color = 1;
                rotateRight(tree, newNode->parent->parent);
            }
        } else {
            // Симметричный случай
        }
    }
    tree->root->color = 0; // Корень всегда черный
}

// Левый поворот дерева относительно заданного узла
void rotateLeft(RBTree *tree, RBNode *node) {
    RBNode *rightChild = node->right;
    node->right = rightChild->left;
    if (rightChild->left != NULL) {
        rightChild->left->parent = node;
    }
    rightChild->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = rightChild;
    } else if (node == node->parent->left) {
        node->parent->left = rightChild;
    } else {
        node->parent->right = rightChild;
    }
    rightChild->left = node;
    node->parent = rightChild;
}

// Правый поворот дерева относительно заданного узла
void rotateRight(RBTree *tree, RBNode *node) {
    RBNode *leftChild = node->left;
    node->left = leftChild->right;
    if (leftChild->right != NULL) {
        leftChild->right->parent = node;
    }
    leftChild->parent = node->parent;
    if (node->parent == NULL) {
        tree->root = leftChild;
    } else if (node == node->parent->right) {
        node->parent->right = leftChild;
    } else {
        node->parent->left = leftChild;
    }
    leftChild->right = node;
    node->parent = leftChild;
}

// Прямой обход красно-черного дерева (в порядке возрастания)
void preorderTraversal(RBNode* node) {
    if (node == NULL) {
        return;
    }
    preorderTraversal(node->left);
    printf("%d ", node->data);
    preorderTraversal(node->right);
}


// Интроспективная сортировка с использованием красно-черного дерева
void introsort(int arr[], int n) {
    // Создаем красно-черное дерево
    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    tree->root = NULL;

    // Вставляем каждый элемент массива в красно-черное дерево
    for (int i = 0; i < n; i++) {
        insertRBNode(tree, arr[i]);
    }

    // Производим прямой обход красно-черного дерева
    // и записываем отсортированные значения обратно в массив
    int i = 0;
    void extractValues(RBNode* node, int arr[], int *i) {
        if (node == NULL) {
            return;
        }
        extractValues(node->left, arr, i);
        arr[(*i)++] = node->data;
        extractValues(node->right, arr, i);
    }
    extractValues(tree->root, arr, &i);

    // Освобождаем память, выделенную для красно-черного дерева
    free(tree);
}

int main() {
    int arr[] = {5, 3, 8, 2, 1, 9, 4, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Исходный массив:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    RBTree *tree = (RBTree*)malloc(sizeof(RBTree));
    tree->root = NULL;
    for (int i = 0; i < n; i++) {
        insertRBNode(tree, arr[i]);
        printf("Добавлен узел %d:\n", arr[i]);
        preorderTraversal(tree->root);
        printf("\n");
    }

    printf("Отсортированный массив:\n");
    preorderTraversal(tree->root);
    printf("\n");

    return 0;
}
