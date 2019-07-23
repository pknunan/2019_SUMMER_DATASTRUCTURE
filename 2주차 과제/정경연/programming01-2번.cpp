#include <stdio.h>
#include <string.h> //오류 검색 - stackoverflow
#include <stdlib.h>
#include <time.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

void check_alphabet(int len, char select_word[], char answer[], char input);

char *buf[CAPACITY];
int n = 0;

int main()
{
	char tmp[BUFFER_SIZE];

	FILE*fp = fopen("harray.txt", "r");
	while (fscanf(fp, "%s", tmp) != EOF) {
		if (strlen(tmp) >= 6)
		{
			buf[n] = strdup(tmp);
			n++;
		}
	}
	fclose(fp);

	back:
	srand(time(NULL));
	int random = rand() % n;
	char select_word[BUFFER_SIZE];   //랜덤하게 선택된 단어
	strcpy(select_word, buf[random]);

	int length = strlen(select_word);
	char answer[BUFFER_SIZE];
	char input;
	for (int i = 0;i < length;i++)
	{
		answer[i] = '*';
	}
	for (int i=0;i < length;i++)
	{
		printf("%c", answer[i]);
	}
	printf("\n");

	while (1) {

		char c;
		if (strcmp(select_word, answer) == 0)
		{
			printf("Try again (y/n) ? ");
			scanf("%c", c);
			if (c == 'y')
				goto back;
			else
				return 0;
		}
		printf("Guess an alphabet: ");
		getchar();
		scanf("%c", &input);
		check_alphabet(length, select_word, answer, input);
	}
	

	return 0;
}
void check_alphabet(int len, char select_word[],char answer[], char input) {
	int p = 0;
	for (int i = 0;i < len;i++)
	{
		if (select_word[i] == input)
		{
			answer[i] = input;
		}
	}
	for (int i = 0;i < len;i++)
	{
		printf("%c", answer[i]);
	}
	printf("\n");
}