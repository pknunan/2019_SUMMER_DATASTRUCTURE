#define _CRT_SECURE_NO_WARNINGS
#define SIZE 6000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

char* coppy(char* str);

int main()
{
	char buffer[50];
	char* words[SIZE] = { NULL, };
	int index = 0;
	int words_count[SIZE] = { 0, };

	srand((unsigned int)time(NULL));

	FILE* fp = fopen("harry.txt", "r");

	while (!feof(fp))
	{
		fscanf(fp, "%s", buffer);
		if (strlen(buffer) >= 6)
		{
			for (int i = 0; i <= index; i++)
			{
				if (i<index && strcmp(buffer, words[i]) == 0)
				{
					words_count[i]++;
					break;
				}
				if (i == index)
				{
					words[i] = coppy(buffer);
					words_count[index]++;
					index++;
					break;
				}
			}
		}
	}
	fclose(fp);


	while (1)
	{
		int rdindex = rand() % index;
		int lth = strlen(words[rdindex]);
		char guess;
		char* tmp = (char*)malloc(lth + 1);
		for (int i = 0; i < lth; i++)
		{
			tmp[i] = '*';
			printf("*");
		}
		printf("\n");
		tmp[lth] = NULL;

		while (1)
		{
			printf("Guess an alphabet: ");
			scanf(" %c", &guess);

			for (int i = 0; i < lth; i++)
			{
				if (words[rdindex][i] == guess)
					tmp[i] = guess;
			}

			printf("%s\n", tmp);
			if (strcmp(tmp, words[rdindex]) == 0)
			{
				printf("Try again (y/n) ? ");
				scanf(" %c", &guess);
				if (guess == 'y')
					break;
				else
					goto EXIT;
			}

		}
	}

	EXIT:
	for (int i = 0; i < index; i++)
		free(words[i]);

	return 0;
}

char* coppy(char* str)
{
	char* p;
	p = (char*)malloc(strlen(str) + 1);
	strcpy(p, str);
	return p;
}
