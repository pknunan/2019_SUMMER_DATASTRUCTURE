#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>
#define buffer_size 20
int duplication(char *buffer);
int n = 0;
char *words[buffer_size];
char buffer[buffer_size];
int count[buffer_size] = { 0 };

int main_1(void) {

	FILE*in_fp = fopen("harry.txt", "r");
	FILE*out_fp = fopen("words.txt", "w");
	
	while (fscanf(in_fp, "%s", buffer) != EOF) {
		if (strlen(buffer) < 6 )
			continue;
		else if (duplication(buffer) != 1) {
			count[duplication(buffer)]++;
			continue;
		}
		else {
			int i = n - 1;
			while (i >= 0 && strcmp(words[i], buffer) > 0)
			{
				words[i + 1] = words[i];
				count[i + 1] = count[i];
				i--;
			}
			words[i + 1] = strdup(buffer);
			count[i + 1] = 0;
		}
		n++;
	}
	fclose(in_fp);

	for (int i = 0; i < n; i++) {
		fprintf(out_fp, "%s %d\n", words[i], count[i]);
	}

	getchar(); getchar();
	return 0;
}
int duplication(char *buffer) {
	for (int i = 0; i < n; i++) {
		if (*words[n] == *buffer)
			return i;
	}
	return 1;
}