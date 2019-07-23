#pragma warning(disable :4996)
#define _CRT_SECURE_NO_WARNING

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 100
#define CAPACITY 100000

char*words_list[CAPACITY];
int n;

void load();
void select();

int main(void)
{
	void load();
	void select();
}
void load()
{
	int i = 0;
	char buffer[CAPACITY];
	FILE *fp = fopen("tabular.txt", "r");
	if (fp==NULL) {
		printf("OPEN FAIL\n");
		exit(1);
	}
	while (! feof(fp)) {
		fscanf(fp, "%s", buffer);
		if (strlen(buffer) >= 6) {
			words_list[i] = strdup(buffer);
			n++;
		}
	}
	fclose(fp);
}
void select()
{
	int i = 0;int j = 0; int size;
	char ch=0;
	char op[BUFFER_SIZE];
	char word[BUFFER_SIZE];

	char buffer[BUFFER_SIZE];
	while (1) 
	{
		i = rand() % n;
		strcpy(buffer, words_list[i]);
		size = strlen(buffer);

		for (j = 0;j < size;j++)
			printf("*");
		for (j = 0;j < size;j++)
			word[j] = '*';

		printf("\n");
		while (1) {

			printf("Guess an alphabet: ");
			scanf("%s",ch);
			for (int k = 0;k < size;k++)
			{
				if (buffer[k] == ch)
				{
					word[k]=ch;
				}	
			}
			for (j = 0;j < size;j++)
				printf("%s", word[j]);
			if (buffer == word)
				break;
		}
		printf("try again (y/n) ?\n");
		scanf("%s",op);
		if (strcmp(op,"n")==0)
			break;
	}
}