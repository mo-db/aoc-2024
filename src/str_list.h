#ifndef STR_LIST_H
#define STR_LIST_H

#include "indefs.h"

// Opaque pointer to the list structure
typedef struct list STR_LIST;

// Create a new list
STR_LIST *str_list_create();

// Destroy a list and free its memory
void str_list_destroy(STR_LIST *list);

// Print the list (useful for testing)
void str_list_print(STR_LIST *list);

// Get the size of the list
int str_list_count(STR_LIST *list);

// Check if the list is empty
int str_list_empty(STR_LIST *list);

// Add an element to the tail of the list
int str_list_append(STR_LIST *list, char *data);

// Add an element to the head of the list
int str_list_prepend(STR_LIST *list, char *data);

void apply_to_all_nodes(STR_LIST *list, char *data,
        int (*f)(char *target, const char *source));

#endif
