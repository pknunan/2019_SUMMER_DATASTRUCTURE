#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char command_line[BUFFER_SIZE];
char buf[CAPACITY];
int n = 0;

int main()
{
	char tmp[BUFFER_SIZE];
	int p, q;
	FILE*in_fp = fopen("tabular.txt", "r");
	fscanf(in_fp, "%d %d", &p, &q);
	FILE*out_fp = fopen("output.txt", "w");
	if (in_fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while (fscanf(in_fp, "%s", tmp) != EOF) {
		buf[n] = strdup(tmp);
		n++;
	}

	char *token;
	char delim[] = '&';
	token = strtok(buf, delim);



	return 0;
}
int read_line(char buf[], int limit)
{
	int ch, i = 0;
	while ((ch = getchar()) != '\\')
		if (i < limit - 1)
			buf[i++] = ch;
	buf[i] = '\0';
	return i;
}