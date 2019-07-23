#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#define MAX 100
char str[MAX];
char answer[MAX];
char *words[MAX];
int n = 0;
void open();
int main() {

	FILE *fp = fopen("harry.txt", "r");						//파일 호출

	while (fscanf(fp, "%s", str) != EOF) {
		if (strlen(str) >= 6) {
			words[n++] = strdup(str);
		}
	}
	fclose(fp);

start:

	srand((unsigned)time(NULL));						//인덱스 랜덤 지정
	int index = rand() % n;
	char ch=0, ans=0;
	int length = strlen(words[index]);
	int result = 0;

	for (int i = 0; i < length; i++) {
		answer[i] = '*';
		printf("*");
	}
	printf("\n");

	char solution[MAX];

	strcpy(solution, words[index]);
	
	while (1) {
		if (result == 1) {
			printf("Try again?(y/n) : ");
			scanf("%c", &ans);
			if (ans == 'y') {
				goto start;
			}
			return;
		}

		printf("Guess an alphabet : ");
		scanf(" %c", &ch);

		for (int i = 0; solution[i] != NULL; i++) {
			if (solution[i] == ch)
				answer[i] = ch;
		}

		if (strcmp(words, answer) == 0) 
			result = 1;
		
		for (int i = 0; i < length; i++)
			printf("%c", answer[i]) ;
		
		printf("\n");
	}
	return 0;
}
