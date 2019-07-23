#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *words[CAPACITY];
char count[CAPACITY];
char *words2[CAPACITY];
int n = 0;
int a = 0;

void frequency();
int main()
{
	char buf[BUFFER_SIZE];

	FILE*in_fp = fopen("harray.txt", "r");
	FILE*out_fp = fopen("words2.txt", "w");
	if (in_fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	
	while (fscanf(in_fp, "%s", buf) != EOF) {
		if (strlen(buf) >= 6)
		{
			int i = n - 1;
			while (i > 0 && strcmp(words[i], buf) > 0) {
				words[i + 1] = words[i];
				i--;
			}
			words[i + 1] = strdup(buf);

			n++;
		}
	}

	frequency();

	for (int i = 0;i <= a;i++)
	{
		fprintf(out_fp,"%s %d\n", words2[i], count[i]);
	}

	return 0;
}

void frequency() {
	char buf[BUFFER_SIZE];
	int p = 0;
	int i;
	for (i = 0;i < n;i++)
	{
		if (strcmp(words[p], words[i]) != 0)
		{
			words2[a] = strdup(words[p]);
			count[a] = i - p;a++;
			p = i;
		}
		if (i == n - 1)
		{
			words2[a] = strdup(words[p]);
			count[a] = i - p + 1;
		}
	}
}