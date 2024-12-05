/**
* bst.h - Header file for ECE 361 hw5 binary search tree
 *
 * @file:               bst.h
 * @author:            	Crow Crossman (crowc.edu)
 * @date:               30-November-2024
 *
 * @brief
 * This is the header file for a binary search tree implementation and associated functions.
 * Based on material from Karumanchi's book and Roy Kravitz's ECE 361 class material.
 *
 */

#ifndef _BST_H
#define _BST_H

#include <stdint.h>

// Structure for storing timestamp data and simulated temperature/humidity readings.
typedef struct temp_humid_data {
    time_t timestamp;
    uint32_t temp;
    uint32_t humid;
} temp_humid_data_t, *temp_humid_data_ptr_t;

// Node structure to be used by BST
typedef struct bst_node {
    temp_humid_data_t data;
    struct bst_node *left;
    struct bst_node *right;
} bst_node_t, *bst_node_ptr_t;

/**
 * @brief Creates a binary search tree (BST) from an array of temperature and humidity data.
 *
 * @param arr Pointer to an array of temp_humid_data_t containing the data.
 * @param size The size of the array.
 * @return bst_node_ptr_t Pointer to the root node of the created BST.
 */
bst_node_ptr_t create_tree(temp_humid_data_t* arr, int size);

/**
 * @brief Creates a single BST node from an array of temperature and humidity data.
 *
 * @param arr Pointer to an array of temp_humid_data_t containing the data for the node.
 * @return bst_node_ptr_t Pointer to the created node.
 */
bst_node_ptr_t create_node(temp_humid_data_t* arr);

/**
 * @brief Inserts a new node with the given data into the BST.
 *
 * @param tree Pointer to the pointer of the root node of the BST.
 * @param data The temp_humid_data_t data to be inserted into the BST.
 */
void insert_node(bst_node_ptr_t* tree, temp_humid_data_t data);

/**
 * @brief Searches the BST for a node with a specific timestamp.
 *
 * @param tree Pointer to the root node of the BST.
 * @param timestamp The timestamp to search for.
 * @return bst_node_ptr_t Pointer to the node containing the matching timestamp, or NULL if not found.
 */
bst_node_ptr_t search_tree(bst_node_ptr_t tree, time_t timestamp);

/**
 * @brief Performs an in-order traversal of the BST, visiting each node in ascending order of timestamp.
 *
 * @param tree Pointer to the root node of the BST.
 */
void traverse_in_order(bst_node_ptr_t tree);

/**
 * @brief Converts a date (month, day, year) into a Unix timestamp.
 *
 * @param month The month.
 * @param day The day of the month.
 * @param year The year.
 * @return time_t The Unix timestamp corresponding to the given date.
 */
time_t con_to_ut(int month, int day, int year);

#endif
