#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#define CAPACITY 100
#define BUFFER_SIZE 20

char* words[CAPACITY];
int n = 0;
void check(char answer[], char guess[], char c);
int main(void)
{
	char buf[BUFFER_SIZE];
	FILE *fp = fopen("harry.txt", "r");
	while (fscanf(fp, "%s", buf) != EOF)
	{
		if (strlen(buf) >= 6)
		{
			words[n] = strdup(buf);
			n++;
		}
	}
	fclose(fp);
	while (1)
	{
		srand((unsigned)time(NULL));
		int j = rand() % n;
		char c, guess[CAPACITY], answer[CAPACITY];
		strcpy(answer, words[j]);
		int length = strlen(answer);
		for (int i = 0; i < length; i++)
		{
			guess[i] = '*';
			printf("%c", guess[i]);
		}	
		printf("\n");
		char k;
		while (1)
		{
			if (strncmp(answer,guess,length)==0)
			{
				printf("Try again(y/n)?");
				scanf(" %c", &k);
				if (k == 'y')
					break;
				else if (k == 'n')
					return 0;
			}
			printf("Guess an alphabet : ");
			char c;
			scanf(" %c", &c);
			check(answer,guess,c);
			for (int i = 0; i<length; i++)
				printf("%c", guess[i]);
			printf("\n");
		}
	}
	return 0;
}
void check(char answer[], char guess[], char c)
{
	for (int i = 0; i < strlen(answer); i++)
	{
		if (answer[i] == c)
			guess[i] = c;
	}
}
