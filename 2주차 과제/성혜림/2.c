#pragma warning (disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define BUFFER_SIZE 20
int guess(char str[], char answer[], char ch);
int read_line(char str[], int limit);
int main_2(void) {

	char *words[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	
	FILE*fp = fopen("harray.txt", "r");
	int n = 0;
	while (fscanf(fp, "%s", buffer) != EOF) {
		if (strlen(buffer) >= 6) {
			words[n] = buffer;
			n++;
		}
	}
	fclose(fp);

	srand((unsigned int)time(NULL));
	char question[BUFFER_SIZE];
	question[n] = words[rand() % n];

	int length = read_line(question, n);
	for (int i = 0; i < length; i++)
		printf("*");

	char answer[BUFFER_SIZE];
	char ch;
	while (1) {
		printf("Guess an alphabet:\n");
		scanf("%c", &ch);
		if (check(question, answer, ch) == 1)
			break;
		getchar();
	}
	printf("Try again(y/n)?\n");
	if(ch=='y')


	getchar(); getchar();
	return 0;
}
int read_line(char str[], int limit) {

	int ch, i = 0;
	while ((ch = getchar()) != '\n') {
		if (i < limit)
			str[i++] = ch;
	}
	str[i] = '\0';
	return i;
}
int guess(char str[], char answer[], char ch) {
	
	for (int i = 0; str[i] != NULL; i++) {
		if (str[i] == ch)
			answer[i] = ch;
	}
	if (strcmp(str, answer) == 0)
		return 1;
	return 0;
}