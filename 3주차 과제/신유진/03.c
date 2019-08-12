#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#define MAX 70000
#define BUFFER_SIZE 50
int main() {
	FILE* fp1 = fopen("harry.txt", "r");
	FILE* fp2 = fopen("aligned.txt", "w");
	int i = 0, j = 0, k = 0, length = 0, gap = 0, n;
	char* buffer;
	char str[20];
	char* line[MAX];
	char* tmp[BUFFER_SIZE];
	char vac[2] = " ";

	while ((fscanf(fp1, "%s", str) != EOF)) {
		strcat(str, vac);
		line[i] = strdup(str);
		int length_prev = length;
		length += strlen(line[i]);
		i++;

		if (length >= 80) {
			n = i - 1;
			gap = 81 - length_prev;
			k = 0;
			buffer = line[n];

			if (length == 80) {

			}

			if (gap > 0) {
				strcat(buffer, vac);
				gap--;
			}

			for (int p = 0; p < gap; p++) {
				fprintf(fp2, "%s ", line[k++]);
			}
			for (; k < n; k++) {
				fprintf(fp2, "%s", line[k]);
			}
			fprintf(fp2, "\n");
			fprintf(fp2, "%s", buffer);
			length = strlen(line[n]);
			i = 0;
		}
	}
	if ((fscanf(fp1, "%s", str) == EOF)) {
		for (int q = n; q < i; q++)
			fprintf(fp2, "%s", line[q]);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}