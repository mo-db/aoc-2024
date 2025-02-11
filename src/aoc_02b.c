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

// one has to compare a-b and b-c to cover all edge cases
int is_save(INT_NODE *a, INT_NODE *b, INT_NODE *c, int (*func)(int a, int b),
		int max_depth)
{
	/* printf("a: %d, b: %d, c: %d\n", a->data, b->data, c->data); */
	int sv = 0;
	if (c->next) {
		// for each unsave level, the recursion forks if there is depth left
		if (func(a->data, b->data) && func(b->data, c->data)) {
			return is_save(b, c, c->next, func, max_depth);
		} else if (max_depth > 0) {
			max_depth--;
			return is_save(a, b, c->next, func, max_depth) ||
				is_save(b, c, c->next, func, max_depth) ||
				is_save(a, c, c->next, func, max_depth);
		} else {
			return 0;
		}
	} else {
		// only if one of the follwing is true the line is save:
		//  - end of list is reached and compare is true
		//  - depth is still > 0
		if (func(a->data, b->data) && func(b->data, c->data)) {
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
	INT_NODE *a, *b, *c;
	int inc_save, dec_save;

	a = b = c = NULL;
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

	// handle first three nodes and return appropreate values
	if (int_list_empty(levels)) {
		int_list_destroy(levels);
		return 0;
	}
	a = levels->head;
	if (a->next) {
		b = a->next;
	} else {
		int_list_destroy(levels);
		return 1;
	}
	if (b->next) {
		c = b->next;
	} else {
		int_list_destroy(levels);
		return 1;
	}

	// check if the list is save for incrementing, then for decrementing
	inc_save = is_save(a, b, c, compare_inc, 1);
	dec_save = is_save(a, b, c, compare_dec, 1);

	int_list_destroy(levels);
	// if either inc or dec were save return 1
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
