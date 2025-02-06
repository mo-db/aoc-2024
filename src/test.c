#include "indefs.h"
#include "util.h"
#include "int_list.h"
#include "str_list.h"

#define FILE_NAME_MAX 500

// hi
int main(int argc, char *argv[])
{
    STR_LIST *arglist = str_list_create();
    printf("List empty: %d\n", str_list_empty(arglist));
    if (argc > 1) {
        for (int i = 1; i < argc; i++) {
            str_list_prepend(arglist, argv[i]);
        }
    }
    apply_to_all_nodes(arglist, "lulu", str_copy_nonull);

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

    char* test = filename;

    char target[] = "blub";
    str_copy(target, test);
    printf("target: %s\n", target);

    FILE* fp = fopen("./src/aoc-01-input", "r");
    assert(fp);

    char *linep = NULL;
    size_t linecapp = 0;
    getline(&linep, &linecapp, fp);
    printf("line: %s\n", linep);
    free(linep);
    fclose(fp);

    return 0;
}
