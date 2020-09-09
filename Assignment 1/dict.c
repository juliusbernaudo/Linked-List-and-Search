#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "list.h"
#define MAX_BUFFER 513
#define FIELD_LEN 129
#define MAX_TITLES 11

/* Created by Julius Miguel Bernaudo 30/08/2020  (jbernaudo@student.unimelb.edu.au) 

Store the data from a csv file into a linked list and search through the data using keys from the stdin and outputting the results to an output text file */
int main(int argc, char **argv) {
    FILE *fp;
	FILE *output;
    int ifTitle = 1;
    char titles[MAX_TITLES][FIELD_LEN];
    char key[FIELD_LEN];
    
    list_t *list;
    list = (list_t*)malloc(sizeof(*list));
    /* Creating the memory for the list */
    assert(list != NULL);
    list -> head = list -> foot = NULL;
    
	output = fopen(argv[2], "w");
	assert(output);
    char line[MAX_BUFFER];
    fp = fopen(argv[1], "r");
    assert(fp);
    
    while(fgets(line, MAX_BUFFER, fp)) {
        int count = 0;
        data_t *data;
        data = (data_t*)malloc(sizeof(*data));
        char *str;
        char tmpArray[MAX_BUFFER];
        char dataArray[MAX_TITLES][MAX_BUFFER];
        str = strtok(line, ",");
        
        /* Checking if this is the first iteration to store the variable titles */
        if(ifTitle == 1) {
            while(str) {
                strcpy(titles[count], str);
                count++;
                str = strtok(NULL, ",");
            }
            if (titles[10][8] == '\n') {
                titles[10][8] = '\0';
            }
            titles[10][8] = 
            ifTitle = 0;
        } else {
            /* Collecting the inputs from the csv by line and splitting up into tokens */
            while(str) {
                /* This is to check if the description or name contains a "," 
                and the rest of the functionality is to remove double quotes and store
                the data */
                if (str[0] == 32 && (count == 8 || count == 6)) {
                    count = count - 1;
                    strcat(dataArray[count], ",");
                    strcpy(tmpArray, str);
                    filter_quotations(tmpArray);
                    strcat(dataArray[count], tmpArray);
                } else if (count == 10) {
                    strcpy(tmpArray, str);
                    filter_quotations(tmpArray);
                    strcpy(dataArray[count], tmpArray);
                } else if (count == 11) {
                    strcpy(tmpArray, str);
                    filter_quotations(tmpArray);
                    filter_newline(tmpArray);
                    strcat(dataArray[count-1], ",");
                    strcat(dataArray[count-1], tmpArray);
                } else {
                    strcpy(tmpArray, str);
                    filter_quotations(tmpArray);
                    strcpy(dataArray[count], tmpArray);
                }
                count++;
                str = strtok(NULL, ",");
            }
            
            /* Data from the line has been stored, now the data struct will be initialised
             so that the data can be inserted into a node and the list */
            initialise_data(data, dataArray);
            insert_data(data, dataArray);
            list = insert_at_foot(list, data);
            free(data);
        }
    }
    
    /* Linked list is created now to read the keys from stdin and search through the data
     for any matches whilst handling any \n that may come along*/
    while (fgets(key, sizeof(key), stdin)) {
        int keylen = strlen(key);
        if (key[keylen-1] == '\n' || key[keylen] == '\n') {
            key[keylen-1] = '\0';
        }
        search_data(list, key, output, titles);
    }
    free_list(list);
	fclose(fp);
	fclose(output);
    return 0;
}