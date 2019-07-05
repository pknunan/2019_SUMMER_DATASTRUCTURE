#define _CRT_SECURE_NO_WARNINGS
#define SIZE 6000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* coppy(char* str);
void sort_words(char** p, int* count, int n);

int main()
{
	char buffer[50];
	char* words[SIZE] = { NULL, };
	int index = 0;
	int words_count[SIZE] = { 0, };

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

	sort_words(words, words_count, index);

	FILE* fp2 = fopen("words.txt", "w");
	int i = 0;
	while (i<index)
	{
		fprintf(fp, "%s: %d\n", words[i], words_count[i]);
		i++;
	}
	fclose(fp2);

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

void sort_words(char** p, int* count, int n)
{
	char* ctmp;
	int itmp;
	for (int i = 0; i < n-1; i++)
		for (int j = 0; j < n-i-1; j++)
			if (strcmp(p[j], p[j + 1]) == 1)
			{
				ctmp = p[j];
				p[j] = p[j+1];
				p[j + 1] = ctmp;

				itmp = *(count+j);
				*(count + j) = *(count + j + 1);
				*(count + j + 1) = itmp;
			}
}
