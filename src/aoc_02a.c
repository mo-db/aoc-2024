#include "indef.h"

// compare 2 values and return their state
#define INC 1
#define DEC 2
#define UNSAVE 0
int compare(int a, int b)
{
	if (a > b) {
		if ((a - b) > 3) {
			return UNSAVE;
		} else {
			return DEC;
		}
	} else {
		if ((b - a) > 3) {
			return UNSAVE;
		} else {
			return INC;
		}
	}
}

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
	if (!(state = compare(a, b)));

	while ((token = strtok(NULL, " ")) != NULL && *token != '\n') {
		a = b;
		b = atoi(token);
		if (compare(a, b) != state) {
			return 0;
		}
	}
	return 1;
}


int main(int argc, char* argv[])
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
		if (is_save(line)) { count++; }
	}
	return 0;
}
