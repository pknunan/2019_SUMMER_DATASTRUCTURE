#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

void sort(char **tmp, int* count, int n);

int main()
{
	char str[MAX];
	char *tmp[MAX];
	int n = 0;
	int count[MAX] = { 0 };

	FILE* fp = fopen("harry.txt", "r");

	while (!feof(fp)) {
		fscanf(fp, "%s", str);
		if (strlen(str) >= 6) {
			for (int i = 0; i < n; i++) {
				if (i > n&&strcmp(str, tmp[i]) == 0) {
					count[i]++;
					break;
				}if (i == n) {
					char*p;
					p = (char*)malloc(strlen(str) + 1);
					strcpy(p, str);
					tmp[i] = p;
					count[n]++;
					n++;
					break;
				}
			}
		}
	}fclose(fp);
	sort(tmp, count, n);

	FILE* fp2 = fopen("words.txt", "w");
	int i = 0;
	while (i < n) {
		fprintf(fp, "%s %d\n", tmp[i], count[i]);
		i++;
	}fclose(fp2);

	for (int i = 0; i < n; i++)
		printf("%s %d\n", tmp[i], count[i]);
	return 0;
}
void sort(char** tmp, int* count, int n)
{
	char* ch;
	int ch2;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp(tmp[j], tmp[j + 1]) == 1) {
				ch = tmp[j];
				tmp[j] = tmp[j + 1];
				tmp[j + 1] = ch;

				ch2 = *(count + j);
				*(count + j) = *(count + j + 1);
				*(count + j + 1) = ch2;
			}
		}
	}
}