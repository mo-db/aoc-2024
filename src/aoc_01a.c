#include "indefs.h"
#include "int_list.h"

#define LOST 100

int print_line(FILE *fp)
{
	char *line = NULL;
	size_t size = 0;
	while (getline(&line, &size, fp) != -1) {
		printf("line: %s\n", line);
	}
	rewind(fp);
	return 1;
}

int count_lines(FILE *fp)
{
	char *line = NULL;
	size_t size = 0;
	int count = 0;
	while (getline(&line, &size, fp) != -1) {
		count++;
	}
	rewind(fp);
	return count;
}

int parse_input(FILE *fp, int lines_n, int *left, int *right)
{
	for (int i = 0; i < lines_n; i++) {
		char left_w[10];
		char right_w[10];
		assert(fscanf(fp, "%s", left_w) != EOF); 
		assert(fscanf(fp, "%s", right_w) != EOF);
		left[i] = atoi(left_w);
		right[i] = atoi(right_w);
	}
	return 1;
}

int sort_ary(int *ary, int len)
{
	int temp = 0;
	int swap = 1;
	while (swap == 1) {
		swap = 0;
		for (int i = 0; i < len-1; i++) {
			if (ary[i] > ary[i+1]) {
				/* printf("ary: %d, ary+1: %d\n", ary[i], ary[i+1]); */
				temp = ary[i];
				ary[i] = ary[i+1];
				ary[i+1] = temp;
				swap = 1;
				/* printf("ary: %d, ary+1: %d\n", ary[i], ary[i+1]); */
			}
		}	
	}
	return 1;
}

int compare(int *left, int *right, int len)
{
	uint32_t sum = 0;
	for (int i = 0; i < len; i++) {
		sum += (left[i] > right[i]) ? left[i] - right[i] : right[i] - left[i];
	} 
	return sum;
}

int main(int argc, char* argv[])
{
	char filename[UINT16_MAX] = "./src/aoc_01_example_input";
    if (argc > 1) {
		strcpy(filename, argv[1]);
    } else {
		printf("using fallback filename\n");

	}
	FILE *fp = fopen(filename, "r");
	assert(fp);

	/* print_line(fp); */
	int lines_n = count_lines(fp);
	int left[lines_n];
	int right[lines_n];
	parse_input(fp, lines_n, left, right);
	/* sort_ary(left, lines_n); */
	/* sort_ary(right, lines_n); */
	for (int i = 0; i < lines_n; i++) {
		printf("left: %d, right: %d\n", left[i], right[i]);
	}
	int sum = compare(left, right, lines_n);
	printf("sum: %d\n", sum);

	print_line(fp);
	printf("lines: %d\n", lines_n);

	fclose(fp);
    return 0;
}
