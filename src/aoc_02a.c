#include "indef.h"

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
	int a, b, state;
	// compare the first two values and set state
	char *token = strtok(line, " ");
	if (token == NULL && *token == '\n') {
		return 0;
	} else {
		a = atoi(token);
	}
	token = strtok(NULL, " ");
	if (token == NULL && *token == '\n') {
		return 0;
	} else {
		b = atoi(token);
	}
	// return if unsave
	if (!(state = compare(a, b))) { return 0; }
	// compare every token with the last and return if unsave
	while ((token = strtok(NULL, " ")) != NULL && *token != '\n') {
		a = b;
		b = atoi(token);
		if (compare(a, b) != state) {
			return 0;
		}
	}
	return 1;
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
	while (getline(&line, &size, stdin) != -1) {
		char *line_copy = strdup(line); // is_save is destructive
		if (is_save(line_copy)) { 
			count++;
			printf("[%d:save] %s", count, line);
		} else {
			printf("[unsave] %s", line);
		}
		free(line_copy);
	}
	printf("save lines: %d\n", count);
	return 0;
}
