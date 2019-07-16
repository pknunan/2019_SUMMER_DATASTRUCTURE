#pragma warning (disable:4996)
#define MAX 1000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void sorting(char** ch, int* count, int num);

int main() {

	char buffer[MAX];
	char* ch[MAX] = { NULL, };
	int num = 0;
	int count[MAX] = { 0, };

	FILE* fp = fopen("harry.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%s", buffer);
		if (strlen(buffer) >= 6) {
			for (int i = 0; i <= num; i++) {
				if (i < num && strcmp(buffer, ch[i]) == 0) {
					count[i]++;
					break;
				}
				if (i == num) {
					char* p;
					p = (char*)malloc(strlen(buffer) + 1);
					strcpy(p, buffer);
					ch[i] = p;
					count[num]++;
					num++;
					break;
				}
			}
		}
	}
	fclose(fp);

	sorting(ch, count, num);

	FILE* fp2 = fopen("words.txt", "w");
	int i = 0;
	while (i < num) {
		fprintf(fp, "%s  %d\n", ch[i], count[i]);
		i++;
	}
	fclose(fp2);

	for (int i = 0; i < num; i++)
		printf("%s   %d\n", ch[i], count[i]);

	getchar(); getchar();
}

void sorting(char** ch, int* count, int num)
{
	char* tmp1;
	int tmp2;
	for (int i = 0; i < num - 1; i++) {
		for (int j = 0; j < num - i - 1; j++) {
			if (strcmp(ch[j], ch[j + 1]) == 1) {
				tmp1 = ch[j];
				ch[j] = ch[j + 1];
				ch[j + 1] = tmp1;

				tmp2 = *(count + j);
				*(count + j) = *(count + j + 1);
				*(count + j + 1) = tmp2;
			}
		}
	}
}