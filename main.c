/**
 * bst_testbench.c - Testbench file for ECE 361 hw 5
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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include "bst.h"
#include "iom361_r2.h"

// typedefs, enums and constants
#define TEMP_RANGE_LOW  42.0
#define TEMP_RANGE_HI   52.0
#define HUMID_RANGE_LOW 72.6
#define HUMID_RANGE_HI  87.3

// global variables
uint32_t* io_base;

#define MAX_CHAR 1000 // Arbitrary big number for buffer

// Prototype functions
void populateBST();

int main(void) {
    int rtn_code;
    float temp, humid;

    // Boilerplate greeting
    printf("ECE 361 - HW 5 - BST and Humidity and Temp Sensors - @author: Crow Crossman (crowc@pdx.edu)\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer large enough to hold the path

    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");

    // Initialize imo361
    printf("Launching imo361 system...\t");
    io_base = iom361_initialize(0, 0, &rtn_code);
    if (rtn_code != 0) {
        // initialization failed
        printf("FATAL(main): Could not initialize I/O module\n");
        return 1;
    }
    printf("Success!\n");

    // Create a month of temp/humidity/timestamp values
    uint32_t temp_value, humid_value;
    float temp_arr[30];
    float humid_arr[30];
    time_t timestamp_arr[30];
    temp_humid_data_t data[30];

    // Since these are made up dates, the goal is to take the temp/humidity values for 30 days of November
    printf("Generating simulated temp and humidity readings for November...\t");
    for (int i = 0; i < 30; i++) {
        _iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
        HUMID_RANGE_HI);
        temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
        temp = (temp_value / powf(2,20)) * 200.0 - 50;
        humid_value = iom361_readReg(io_base, HUMID_REG, NULL);
        humid = (humid_value/ pow(2, 20)) * 100;

        temp_arr[i] = temp;
        humid_arr[i] = humid;
        timestamp_arr[i] = con_to_ut(11, i + 1, 2024);

        data[i].timestamp = timestamp_arr[i];
        data[i].temp = temp_arr[i];
        data[i].humid = humid_arr[i];
    }
    printf("Success!\n");

    printf("Shuffling values...\t");
    // Shuffle shuffle shuffle
    srand(time(NULL));
    temp_humid_data_t shuffled_deck[30];
    int banlist[30] = {0};
    // Pick a number between 1 and 30, place item 1 there, now randomly pick next number, etc...
    int random_pick = 0;
    for (int i = 0; i < 30; i++) {
        int r = (rand() % 30);
        // Check if r has been used already
        while (banlist[r] == 1) {
            r = (rand() % 30);
        }
        shuffled_deck[r] = data[i];
        //printf("Position %d in deck got shuffled to position %d\n", i, r);
        banlist[r] = 1;
    }
    printf("Success!\n");

    printf("Growing a tree...\t");
    // Create our tree with shuffled order
    int size = sizeof(data) / sizeof(data[0]);
    bst_node_ptr_t tree = create_tree(shuffled_deck, size);
    printf("Success!\n\n");

    // Our main loop to get input
    char buffer[MAX_CHAR];
    int i = 0;

    printf("Please enter a date to search in format: MM/DD/YYYY\n");
    while (i < MAX_CHAR - 1) {
        char c = getchar();
        if (c == '\n') {
            if (i == 0) {
                break;
            }
            buffer[i] = '\0';
            printf("You entered: %s\n", buffer);
            int m, d, y;
            if (sscanf(buffer, "%d/%d/%d", &m, &d, &y) == 3) {   // Cool format handling found on stackoverflow (https://stackoverflow.com/questions/1412513/getting-multiple-values-with-scanf)
                printf("Searching for timestamp...\n");
                search_tree(tree,con_to_ut(m, d, y));
            } else {
                printf("Invalid format.\n");
            }

            i = 0;
            printf("--------------------------------------------\n");
        } else {
            buffer[i++] = c;
        }
    }

    // Print in-order traversal
    printf("In-order traversal:\n\n");
    traverse_in_order(tree);

    return 0;
}
