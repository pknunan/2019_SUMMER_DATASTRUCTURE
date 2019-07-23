#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define MAX 10000
#define SIZE 81

int main() {

	char *ch[MAX], buffer[SIZE];
	int n = 0;
	FILE *fp1 = fopen("harry.txt", "r");
	FILE *fp2 = fopen("aligned.txt", "w");

	while (!feof(fp1)) {
		fscanf(fp1, "%s", buffer);
		ch[n++] = strdup(buffer);
	}
	fclose(fp1);

	int count = 0, num = 0, i = 0;
	char buffer1[SIZE], buffer2[SIZE];
	while (num < n) {
		int len = strlen(ch[num]) - 1;
		if (i > 0) {
			count += len - i;
			i = 0;
			strcat(buffer1, buffer2);
			while (*buffer2 != '\0') {
				*buffer2 = '\0';
				(*buffer2)++;
			}
		}
		else {
			count += len;
			strcat(buffer1, ch[num]);
		}

		num++;

		if (count > 80) {
			num--;
			count -= len;
			while (count < 80) {
				char str = ch[num][i];
				int Blen = strlen(buffer1);
				buffer1[Blen + 1] = '\0';
				buffer1[Blen] = str;
				i++;
				count++;
			}
			fprintf(fp2, "%s\n", buffer1);

			for (int k = i; i < len + 2; k++) {
				char str = ch[num][k];
				int Blen2 = strlen(buffer2);
				buffer2[Blen2] = str;
			}
			count = 0;
			while (*buffer1 != '\0') {
				*buffer1 = '\0';
				(*buffer1)++;
			}
		}
	}

	char BUF[SIZE];
	FILE *fp3 = fopen("aligned.txt", "r");
	while (!feof(fp3)) {
		fscanf(fp3, "%s", BUF);
		printf("%s", BUF);
	}
	fclose(fp3);

	getchar(); getchar();
}