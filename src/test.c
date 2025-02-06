#include "util.h"
#include "int_list.h"
#include "str_list.h"
#include <stdio.h>
#include <stdlib.h>

#define FILE_NAME_MAX 500

int main(int argc, char *argv[])
{
    STR_LIST *arglist = str_list_create();
    printf("List empty: %d\n", str_list_empty(arglist));
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            str_list_prepend(arglist, argv[i]);
        }
    }
    printf("List empty: %d\n", str_list_empty(arglist));
    printf("List count: %d\n", str_list_count(arglist));
    str_list_print(arglist);
    if (str_list_empty(arglist) == 0) {
        str_list_destroy(arglist);
    }

    STR_LIST *files = str_list_create();
    char filename[FILE_NAME_MAX];
    printf("put filename: ");
    scanf("%s", filename);
    printf("%s\n", filename);

    char blub[] = "BLUB";
    char* file = filename;
    char* test = blub;
    char* testit = NULL;

    int count = 0;
    while (*test) { 
        count++;
        *test++ = *file++;
    }

    if (*test == '\0') { 
        printf("test is NULL\n");
        printf("test is %s\n", blub);
    } else {
        printf("test is %c, count: %d\n", *test, count);
    }

    return 0;
}
