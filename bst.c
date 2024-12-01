#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bst.h"

bst_node_ptr_t create_new_node(temp_humid_data_t data) {
    bst_node_ptr_t new_node = (bst_node_ptr_t)malloc(sizeof(bst_node_t));
    if (new_node == NULL) {
        printf("Error! Memory allocation failed.\n");
        return NULL;
    }
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

void insert_node(bst_node_ptr_t* tree, temp_humid_data_t data) {
    if (*tree == NULL) {
        *tree = create_new_node(data);
        return;
    }

    if (data.timestamp <= (*tree)->data.timestamp) {
        insert_node(&(*tree)->left, data);
    } else {
        insert_node(&(*tree)->right, data);
    }
}

bst_node_ptr_t create_tree(temp_humid_data_t* arr, int size) {
    if (size <= 0) return NULL;

    bst_node_ptr_t root = NULL;
    for (int i = 0; i < size; i++) {
        insert_node(&root, arr[i]);
    }
    return root;
}

void traverse_in_order(bst_node_ptr_t tree) {
    if (tree == NULL) return;

    traverse_in_order(tree->left);
    printf("Timestamp: %ld, Temp: %u, Humid: %u\n", tree->data.timestamp, tree->data.temp, tree->data.humid);
    traverse_in_order(tree->right);
}
