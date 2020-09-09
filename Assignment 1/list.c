#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <math.h>
#include "list.h"
#define MAX_BUFFER 513
#define MAX_OUTPUT 613
#define FIELD_LEN 129
#define MAX_TITLES 11

void
free_data(data_t *data) {
    free(data->year);
    free(data->block);
    free(data->property);
    free(data->base);
    free(data->city);
    free(data->name);
    free(data->code);
    free(data->desc);
    free(data->xCoord);
    free(data->yCoord);
    free(data->location);
}

/* Stuff from listops.c */
/* =====================================================================
   Programs (free_list) and (insert_at_foot) were written by Alistair Moffat, as an
   example for the book and modified by me, Julius Miguel Bernaudo
   "Programming, Problem Solving, and Abstraction with C", Pearson
   Custom Books, Sydney, Australia, 2002; revised edition 2012,
   ISBN 9781486010974.

   See http://people.eng.unimelb.edu.au/ammoffat/ppsaa/ for further
   information.

   Prepared December 2012 for the Revised Edition.
   ================================================================== */
void
free_list(list_t *list) {
	node_t *curr, *prev;
	assert(list!=NULL);
	curr = list->head;
	while (curr) {
		prev = curr;
		curr = curr->next;
        free_data(&(prev -> data));
		free(prev);
	}
	free(list);
}

list_t
*insert_at_foot(list_t *list, data_t *value) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = *value;
	new->next = NULL;
    
	if (list->foot==NULL) {
		/* this is the first insertion into the list */
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

/* Simple function created to store the data into the data struct so 
that my code is not as messy */
void
insert_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]) {
    strcpy(data -> year, dataArray[0]);
    strcpy(data -> block ,dataArray[1]);
    strcpy(data -> property ,dataArray[2]);
    strcpy(data -> base ,dataArray[3]);
    strcpy(data -> city ,dataArray[4]);
    strcpy(data -> name ,dataArray[5]);
    strcpy(data -> code ,dataArray[6]);
    strcpy(data -> desc ,dataArray[7]);
    strcpy(data -> xCoord ,dataArray[8]);
    strcpy(data -> yCoord ,dataArray[9]);
    strcpy(data -> location ,dataArray[10]);
}

/* Same purpose as insert_data, however this is to intialise the data struct
and keep the code clean and simple to read */
void 
initialise_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]) {
    data -> year = (char *)malloc(strlen(dataArray[0])+1*sizeof(char));
    data -> block = (char *)malloc(strlen(dataArray[1])+1*sizeof(char));
    data -> property = (char *)malloc(strlen(dataArray[2])+1*sizeof(char));
    data -> base = (char *)malloc(strlen(dataArray[3])+1*sizeof(char));
    data -> city = (char *)malloc(strlen(dataArray[4])+1*sizeof(char));
    data -> name = (char *)malloc(strlen(dataArray[5])+1*sizeof(char));
    data -> code = (char *)malloc(strlen(dataArray[6])+1*sizeof(char));
    data -> desc = (char *)malloc(strlen(dataArray[7])+1*sizeof(char));
    data -> xCoord = (char *)malloc(strlen(dataArray[8])+1*sizeof(char));
    data -> yCoord = (char *)malloc(strlen(dataArray[9])+1*sizeof(char));
    data -> location = (char *)malloc(strlen(dataArray[10])+1*sizeof(char));
}

/* Scans through the list searching for any string matches with the key */
void
search_data(list_t *list, char *key, FILE *output, char titles[MAX_TITLES][FIELD_LEN]) {
    int cmpResult;
    int matchFound = 1;
    node_t *curr;
    curr = (node_t*)malloc(sizeof(*curr));
    assert(curr!=NULL);
    curr = list -> head;
    
    /* Traversing the linked list and using the string comparison tool 
    to check whether the key and name match */
    while(curr) {
        cmpResult = strcmp(curr -> data.name, key);
        if (cmpResult == 0) {
            output_string(&(curr -> data), output, titles);
            matchFound = cmpResult;
        }
        curr = curr -> next;
    }
    free(curr);
    if (matchFound != 0) {
        fputs(key, output);
        fputs(" -->NOTFOUND\n", output);
    }
}

/* Removing any double quotations from the data while maintaining
any quotations that are part of the string itself */
void
filter_quotations(char *array) {
    int i = 0, len = strlen(array), j;
    while(i<len) {
        if (array[i] == 34 && array[i+1] != 34) {
            j = i;
            while(j<len){
                array[j] = array[j+1];
                j++;
            }
        }
        if (array[i] == 34 && array[i+1]) {
            j = i;
            while(j<len){
                array[j] = array[j+1];
                j++;
            }
        }
        i++;
        len = strlen(array);
    }
}

/* Remove any newlines trailing at the end of the data */
void
filter_newline(char *array) {
    int i = 0, len = strlen(array), j;
    while(i<len) {
        if (array[i] == '\n' || array[i] == '\r') {
            j = i;
            while(j<len){
                array[j] = array[j+1];
                j++;
            }
        } else {
            i++;
        }
        len = strlen(array);
    }
}

/* Generate an output string that is to be outputted to the text file
while keeping the code within other functions easier to understand */
void
output_string(data_t *data, FILE *output, char titles[MAX_TITLES][FIELD_LEN]) {
    char outputStr[MAX_OUTPUT];
    strcpy(outputStr, data -> name);
    strcat(outputStr, " --> ");
    strcat(outputStr, titles[0]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> year);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[1]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> block);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[2]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> property);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[3]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> base);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[4]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> city);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[6]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> code);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[7]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> desc);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[8]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> xCoord);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[9]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> yCoord);
    strcat(outputStr, " || ");
    strcat(outputStr, titles[10]);
    strcat(outputStr, ": ");
    strcat(outputStr, data -> location);
    strcat(outputStr, " || ");
    strcat(outputStr, "\n");
    fputs(outputStr, output);
}