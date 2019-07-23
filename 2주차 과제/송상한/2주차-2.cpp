#define _crt_secure_no_warnings
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define buffer_size 100000

char star[30];
char *words[buffer_size] = { NULL };
int count = 0;
char tmp[100];

void hangman();
int str_ch(const char*s, int c);
int main(void)
{
	FILE *fp = fopen("harry.txt", "r");
	while (!feof(fp))
	{
		fscanf(fp, "%s", tmp);
		if (strlen(tmp) >= 6) {
			for (int i = 0; i <= count; i++) {
				if (i < count && strcmp(words[i], tmp) == 0)
					break;
				if (i == count)
				{
					words[count++] = strdup(tmp);
					break;
				}
			}
		}
	}
	fclose(fp);
	srand((unsigned)time(NULL));


	while (1) {
		hangman();
		printf("Try again (y/n) ?  ");
		int s;
		char z[10];
		scanf("%s", z);
		s = z[0];
		if (s == 'y')
			continue;
		else
			break;
	}



	return 0;

}

void hangman()
{
	srand((unsigned)time(NULL));

	int random_count = rand() % count;
	int random_count_len = strlen(words[random_count]);
	//printf("%d\n", random_count_len);
	//printf("%s\n", words[random_count]);

	for (int i = 0; i < random_count_len; i++)
		star[i] = '*';

	star[random_count_len] = '\0';
	printf("%s", star);
	printf("\n");
	char tmp1[20];
	int ch;
	while (1) {
		printf("Guess an alphabet : ");
		scanf("%s", tmp1);
		ch = tmp1[0];
		int idx = str_ch(words[random_count], ch);
		if (idx == -1)
			printf("%s\n", star);
		else {
			star[idx] = ch;
			printf("%s\n", star);
		}
		if (strcmp(star, words[random_count]) == 0)
			break;
	}
}

int str_ch(const char*s, int c)
{
	int i = 0;
	c = (char)c;
	while (1) {
		if (s[i] == '\0')
			return -1;
		else if (s[i] == c && star[i] == '*')
			return i;
		i++;
	}
}
