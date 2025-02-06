#include "str_list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>

typedef struct node {
    char *data;
    struct node *next;
} STR_NODE;

typedef struct list {
    STR_NODE *head;
    int count;
} STR_LIST;

STR_LIST *str_list_create()
{
    STR_LIST *list = malloc(sizeof(STR_LIST));
    assert(list);
    list->head = NULL;
    list->count = 0;
    return list;
}

static void _node_destroy(STR_NODE *node)
{
    if (node->next != NULL) { 
        _node_destroy(node->next);
    }
    printf("node: %s\n", node->data);
    free(node->data);
    free(node);
}

void str_list_destroy(STR_LIST *list)
{
    assert(list);
    assert(list->head);
    _node_destroy(list->head);
    free(list);
}

void str_list_print(STR_LIST *list)
{
    STR_NODE *current = list->head;
    while (current) {
        printf("%s\n", current->data);
        current = current->next;
    }
}

int str_list_count(STR_LIST *list)
{
    assert(list);
    return list->count;
}

int str_list_empty(STR_LIST *list)
{
    assert(list);
    if (list->head == NULL)
        return 1;
    else
        return 0;
}

// node specific functions
int str_list_append(STR_LIST *list, char *data)
{
    assert(list);
    assert(data);

    STR_NODE *new_node = malloc(sizeof(STR_NODE));
    assert(new_node);

    new_node->data = strdup(data);
    new_node->next = NULL;

    if (list->head == NULL) {
        list->head = new_node;
    } else {
        STR_NODE *current = list->head;
        for (;;) {
            if (current->next == NULL) {
                current->next = new_node;
                break;
            } else {
                current = current->next;
            }
        }
    }
    list->count++;
    return 1;
}

int str_list_prepend(STR_LIST *list, char *data)
{
    // check if parameters are NULL, alloc new node
    assert(list);
    assert(data);
    STR_NODE *new_node = malloc(sizeof(STR_NODE));
    assert(new_node);
    // setting to NULL to avoid mem errors
    new_node->data = strdup(data);
    new_node->next = NULL;
    // head gets address of new_node, new_node->next gets address of prev node
    new_node->next = list->head;
    list->head = new_node;
    list->count++;
    return 1;
}
