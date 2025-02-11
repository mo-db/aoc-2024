#include "indef.h"
#include "int_list.h"
#include <math.h>

// compare 2 values for the given rules
int compare(int a, int b)
{
	if (a > b) {
		if ((a - b) > 3) {
			return 0;
		} else {
			return 2; // decreasing
		}
	} else if (b > a) {
		if ((b - a) > 3) {
			return 0;
		} else {
			return 1; // increasing
		}
	} else {
		return 0;
	}
}


// check if lines fulfills the rules for a save line
int is_save(char *line)
{
	INT_LIST *levels = int_list_create();

	int num = 0;
	int expo = 0;
	for (char *c = line; *c != '\n'; c++) {
		if (*c == ' ') {
			int_list_prepend(levels, num);
			expo = num = 0;
		} else {
			num += (*c - '0') * pow(10, expo++);
		}
	}
	int_list_prepend(levels, num);
	int_list_reverse(levels);


	int_list_print(levels);
	int_list_destroy(levels);
	return 1;
}

int main()
{
    if (freopen("./src/aoc_02_ex_input", "r", stdin) == NULL)
    {
       perror("freopen() failed");
       return 1;
    }
	char *line = NULL;
	size_t size = 0;
	int count = 0;
	while (getline(&line, &size, stdin) != -1) {
		is_save(line);
		/* char *line_copy = strdup(line); // is_save is destructive */
		/* if (is_save(line_copy)) {  */
		/* 	count++; */
		/* 	printf("[%d:save] %s", count, line); */
		/* } else { */
		/* 	printf("[unsave] %s", line); */
		/* } */
		/* free(line_copy); */
	}
	printf("save lines: %d\n", count);
	return 0;
}
