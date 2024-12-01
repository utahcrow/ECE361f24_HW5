/**
* test.c - Testbench file for ECE 361 hw 5
 *
 * @file:               test.c
 * @author:             Crow Crossman (crowc.edu)
 * @date:               30-November-2024
 * @version:    1.0
 *
 * @brief
 * Testbench to determine whether my BST implementation works.
 *
 */

#include <stdio.h>
#include "bst.h"

#define MAX_CHAR 1000

int main(void) {
    // Create our search tree
    temp_humid_data_t test_arr[] = {{0,10,40},{1,20,50},{2,30,60}};

    int size = sizeof(test_arr) / sizeof(test_arr[0]);
    bst_node_ptr_t tree = create_tree(test_arr, size);

    printf("In-order traversal:\n");
    traverse_in_order(tree);

    printf("Back to main.\n");

    // Our main loop to get input
    char buffer[MAX_CHAR];
    int i = 0;
    while (i < MAX_CHAR - 1) {
        char c = getchar();
        if (c == '\n') {
            if (i == 0) {
                break;
            }
            buffer[i] = '\0';
            printf("You entered: %s\n", buffer);
            i = 0;
        } else {
            buffer[i++] = c;
        }
    }

    return 0;
}
