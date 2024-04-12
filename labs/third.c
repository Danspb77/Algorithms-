#include <stdio.h>
#include <stdlib.h>

typedef enum { RED, BLACK } node_color;

typedef struct rb_node {
    int value;
    node_color color;
    struct rb_node *left, *right, *parent;
} rb_node;

rb_node* create_rb_node(int value) {
    rb_node *node = malloc(sizeof(rb_node));
    node->value = value;
    node->color = RED;
    node->left = node->right = node->parent = NULL;
    return node;
}

void left_rotate(rb_node **root, rb_node *x) {
    rb_node *y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->left) {
        x->parent->left = y;
    } else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

void right_rotate(rb_node **root, rb_node *x) {
    rb_node *y = x->left;
    x->left = y->right;
    if (y->right != NULL) {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        *root = y;
    } else if (x == x->parent->right) {
        x->parent->right = y;
    } else {
        x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
}

void rb_insert_fixup(rb_node **root, rb_node *z) {
    while (z != *root && z->parent->color == RED) {
        if (z->parent == z->parent->parent->left) {
            rb_node *y = z->parent->parent->right;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->right) {
                    z = z->parent;
                    left_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                right_rotate(root, z->parent->parent);
            }
        } else {
            rb_node *y = z->parent->parent->left;
            if (y && y->color == RED) {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            } else {
                if (z == z->parent->left) {
                    z = z->parent;
                    right_rotate(root, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                left_rotate(root, z->parent->parent);
            }
        }
    }
    (*root)->color = BLACK;
}

void rb_insert(rb_node **root, rb_node *node) {
    rb_node *y = NULL;
    rb_node *x = *root;
    while (x != NULL) {
        y = x;
        if (node->value < x->value) {
            x = x->left;
        } else {
            x = x->right;
        }
    }
    node->parent = y;
    if (y == NULL) {
        *root = node;
    } else if (node->value < y->value) {
        y->left = node;
    } else {
        y->right = node;
    }
    node->color = RED;
    rb_insert_fixup(root, node);
}

void inorder_traversal(rb_node *root) {
    if (root != NULL) {
        inorder_traversal(root->left);
        printf("%d ", root->value);
        inorder_traversal(root->right);
    }
}

int main() {
    rb_node *root = NULL;
    int values[] = {7, 3, 18, 10, 22, 8, 11, 26};
    for (int i = 0; i < sizeof(values)/sizeof(values[0]); i++) {
        rb_insert(&root, create_rb_node(values[i]));
    }
    inorder_traversal(root);
    return 0;
}
