#include "indef.h"
#include "int_list.h"

int compare_dec(int a, int b)
{
	if (a > b && (a - b) <= 3)
		return 1;
	else
		return 0;
}

int compare_inc(int a, int b)
{
	if (b > a && (b - a) <= 3)
		return 1;
	else
		return 0;
}

// the maxdepth stands for how many levels can be skipped and still be save
// can always relate to 3 values, so i need prev
int is_save(INT_NODE *current, INT_NODE *next, int (*func)(int a, int b),
		int max_depth)
{
	if (next->next) {
		// for each unsave level, the recursion forks if there is depth left
		if (func(current->data, next->data)) {
			return is_save(next, next->next, func, max_depth);
		} else if (max_depth > 0) {
			max_depth--;
			return is_save(current, next->next, func, max_depth);
			return is_save(next, next->next, func, max_depth);
		} else {
			return 0;
		}
	} else {
		// only if one of the follwing is true the line is save:
		//  - end of list is reached and compare is true
		//  - depth is still > 0
		if (func(current->data, next->data)) {
			return 1;
		} else if (max_depth > 0) {
			return 1;
		} else {
			return 0;
		}
	}
}

// check if lines fulfills the rules for a save line
int process_line(char *line)
{
	INT_LIST *levels = int_list_create();
	INT_NODE *current, *next;
	int inc_save, dec_save;

	current = next = NULL;
	inc_save = dec_save = 0;

	// fill the list
	char num[10];
	char *numptr = num;
	for (char *c = line; *c != '\n'; c++) {
		if (*c == ' ') {
			*numptr = '\0';
			int_list_prepend(levels, atoi(num));
			numptr = num;
		} else {
			*numptr++ = *c;
		}
	}
	*numptr = '\0';
	int_list_prepend(levels, atoi(num));
	int_list_reverse(levels);

	// handle first two nodes
	if (int_list_empty(levels)) {
		int_list_destroy(levels);
		return 0;
	}
	current = levels->head;
	if (current->next) {
		next = current->next;
	} else {
		int_list_destroy(levels);
		return 1;
	}

	inc_save = is_save(current, next, compare_inc, 1);
	dec_save = is_save(current, next, compare_dec, 1);

	/* int_list_print(levels); */
	int_list_destroy(levels);
	
	return MAX(inc_save, dec_save);
}

int main()
{
    if (freopen("./src/aoc_02_input", "r", stdin) == NULL)
    {
       perror("freopen() failed");
       return 1;
    }
	char *line = NULL;
	size_t size = 0;
	int count = 0;
	const int SAVE = 1;
	while (getline(&line, &size, stdin) != -1) {
		if (process_line(line) == SAVE) {
			count++;
			printf("[%.3d:save] %s", count, line);
		} else {
			printf("[::unsave] %s", line);
		}
	}
	printf("save lines: %d\n", count);
	return 0;
}
