/**
* bst.h - Header file for ECE 361 hw5 binary search tree
 *
 * @file:               bst.h
 * @author:            	Crow Crossman (crowc.edu)
 * @date:               30-November-2024
 * @version:    1.0
 *
 * @brief
 * This is the header file for a binary search tree implementation and associated functions.
 * Based on material from Karumanchi's book.
 *
 */

#ifndef _BST_H
#define _BST_H

#include <time.h>
#include <stdint.h>

#include <stdint.h>
#include <time.h>

typedef struct temp_humid_data {
    time_t timestamp;
    uint32_t temp;
    uint32_t humid;
} temp_humid_data_t, *temp_humid_data_ptr_t;

typedef struct bst_node {
    temp_humid_data_t data;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t, *bst_node_ptr_t;

bst_node_ptr_t create_tree(temp_humid_data_t* arr, int size);

bst_node_ptr_t create_node(temp_humid_data_t* arr);

void insert_node(bst_node_ptr_t* tree, temp_humid_data_t data);

bst_node_ptr_t search_tree(bst_node_ptr_t tree, time_t timestamp);

void traverse_in_order(bst_node_ptr_t tree);

time_t con_to_ut(char* arr);


#endif
