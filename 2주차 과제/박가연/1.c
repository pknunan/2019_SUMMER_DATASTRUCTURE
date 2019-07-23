#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char* words[CAPACITY];
int numbers[CAPACITY] = { 0 }, n = 0;

int search(char *buf);
int main(void)
{
	char buf[30];
	FILE *fp = fopen("harry.txt", "r");
	FILE *fp2 = fopen("words.txt", "w");
	while (fscanf(fp, "%s", buf) != EOF)
	{
		if(strlen(buf)<6)
			continue;
		else if (search(buf) != -1)
		{
			numbers[search(buf)]++;
			continue;
		}
		else
		{
			int i = n - 1;
			while (i >= 0 && strcmp(words[i], buf) > 0)
			{
				words[i + 1] = words[i];
				numbers[i + 1] = numbers[i];
				i--;
			}
			words[i + 1] = strdup(buf);
			numbers[i + 1] = 0;
		}
		n++;
	}
	for (int i = 0; i < n; i++)
		fprintf(fp2, "%s %d\n", words[i], numbers[i]+1);
	fclose(fp);
	fclose(fp2);
	return 0;
}
int search(char *buf)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(buf,words[i])==0)
			return i;
	}
	return -1;
}