#ifndef INT_LIST_H
#define INT_LIST_H

// Opaque pointer to the int_list structure
typedef struct list INT_LIST;

// Create a new int_list
INT_LIST *list_create();

// Destroy a int_list and free its memory
void int_list_destroy(INT_LIST *list);

// Print the int_list (useful for testing)
void int_list_print(INT_LIST *list);

// Get the size of the int_list
int int_list_count(INT_LIST *list);

// Check if the int_list is empty
int int_list_empty(INT_LIST *list);

// Add an element to the tail of the int_list
int int_list_append(INT_LIST *list, int data);

// Add an element to the head of the int_list
int int_list_prepend(INT_LIST *list, int data);

#endif
