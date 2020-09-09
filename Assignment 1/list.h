#ifndef LISTH
#define LISTH
#define MAX_BUFFER 513
#define FIELD_LEN 129
#define MAX_TITLES 11

typedef struct data {
    char* year;
    char* block;
    char* property;
    char* base;
    char* city;
    char* name;
    char* code;
    char* desc;
    char* xCoord;
    char* yCoord;
    char* location;
    
} data_t;

typedef struct node {
    data_t data;
    struct node* next;
} node_t;

typedef struct list {
    node_t* head;
    node_t* foot;
} list_t;

void free_data(data_t *data);
void free_list(list_t *list);
list_t *insert_at_foot(list_t *list, data_t *data);
void insert_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]);
void initialise_data(data_t *data, char dataArray[MAX_TITLES][MAX_BUFFER]);
void search_data(list_t *list, char *key, FILE *output, char titles[MAX_TITLES][FIELD_LEN]);
void filter_newline(char *array);
void filter_quotations(char *array);
void output_string(data_t *data, FILE *output, char titles[MAX_TITLES][FIELD_LEN]);

#endif
