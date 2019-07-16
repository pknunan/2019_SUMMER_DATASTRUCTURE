#pragma warning (disable:4996)
#define MAX 10000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

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

	srand((unsigned int)time(NULL));
	while (1) {
		int random = rand() % num;
		int len = strlen(ch[random]);
		char guess;
		char TRY;
		char* word = (char*)malloc(len + 1);
		for (int i = 0; i < len; i++) {
			word[i] = '*';
			printf("*");
		}
		printf("\n");
		word[len] = NULL;

		while (1) {
			printf("Guess an alphabet: ");
			scanf(" %c", &guess);

			for (int i = 0; i < len; i++) {
				if (ch[random][i] == guess)
					word[i] = guess;
			}

			printf("%s\n", word);
			if (strcmp(word, ch[random]) == 0) {
				printf("Try again (y/n) ? ");
				scanf(" %c", &TRY);
				break;
			}
		}
		if (TRY == 'n')
			break;
	}

	getchar(); getchar();
}