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

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "bst.h"
#include "iom361_r2.h"

// typedefs, enums and constants
#define TEMP_RANGE_LOW  42.0
#define TEMP_RANGE_HI   52.0
#define HUMID_RANGE_LOW 72.6
#define HUMID_RANGE_HI  87.3

 // global variables
 uint32_t* io_base;

#define MAX_CHAR 1000

// Prototype functions
void populateBST();

int main(void) {
    int rtn_code;
    //uint32_t reg_value;
    float temp, humid;

    // greet the user and display the working directory for the application
    printf("ECE 361 - HW 5 - BST and Humidity and Temp Sensors (crowc@pdx.edu)\n");
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

    // initialize IO module
    printf("System Launch: Initialize\n");
    io_base = iom361_initialize(16, 16, &rtn_code);
    if (rtn_code != 0) {
        // initialization failed
        printf("FATAL(main): Could not initialize I/O module\n");
        return 1;
    }
    printf("\n");

    // set a new temperature and humidity and display it
    uint32_t temp_value, humid_value;
    float temp_arr[31];
    float humid_arr[31];
    time_t timestamp_arr[31];
    temp_humid_data_t data[31];

    for (int i = 0; i < 31; i++) {
        _iom361_setSensor1_rndm(TEMP_RANGE_LOW, TEMP_RANGE_HI, HUMID_RANGE_LOW,
        HUMID_RANGE_HI);
        temp_value = iom361_readReg(io_base, TEMP_REG, NULL);
        temp = (temp_value / powf(2,20)) * 200.0 - 50;
        humid_value = iom361_readReg(io_base, HUMID_REG, NULL);
        humid = (humid_value/ pow(2, 20)) * 100;

        char date[124];
        char month = "11/";
        char year = "/2024";
        char day[2];
        sprintf(day, "%d", i + 1);
        strcat(date, &month);
        strcat(date, day);
        strcat(date, &year);
        temp_arr[i] = temp;
        humid_arr[i] = humid;
        timestamp_arr[i] = con_to_ut(date);

        data[i].timestamp = timestamp_arr[i];
        data[i].temp = temp_arr[i];
        data[i].humid = humid_arr[i];
    }
    printf("\n");

    // Create our search tree
    int size = sizeof(data) / sizeof(data[0]);
    bst_node_ptr_t tree = create_tree(data, size);

    printf("In-order traversal:\n\n");
    traverse_in_order(tree);

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
            printf("Searching for timestamp...\n");
            search_tree(tree,con_to_ut(buffer));
            i = 0;
        } else {
            buffer[i++] = c;
        }
    }

    return 0;
}
