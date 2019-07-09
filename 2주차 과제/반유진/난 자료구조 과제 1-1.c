#include <stdio.h>
#include <string.h>
#define MAX 100
int main(void) {
	char str[MAX][MAX], tmp[MAX];
	int same[MAX];
	int n = 0;

	FILE *in_fp = fopen("harry.txt", "r");
	FILE *out_fp = fopen("words.txt", "w");

	while (!feof(in_fp)) fscanf(in_fp, "%s", &str[n++]);

	for (int i = 0; i < n; i++)
		fscanf(in_fp, "%s", &str[i]);

	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < i; j++) {
			if (strcmp(str[j], str[j + 1]) > 0) {
				strcpy(tmp, str[j]);
				strcpy(str[j], str[j + 1]);
				strcpy(str[j + 1], tmp);
			}
		}
	}
	for (int i = 0; i < n; i++) 
		same[i] = 1;
	
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (strcmp(str[i], str[j]) == 0) {
				same[i] += 1;
				same[j] += 1;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		if (strlen(str[i]) >= 6) {
			if (strcmp(str[i], str[i + 1]) != 0) {
				fprintf(out_fp, "%s ", str[i]);
				fprintf(out_fp, "%d\n", same[i]);
			}
		}
	}
	fclose(in_fp);
	fclose(out_fp);

	return 0;
}