#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INIT_CAPACITY 100
#define BUFFER_SIZE 100

int read_line(char str[], int limit);
int capacity = INIT_CAPACITY;
int sum, num = 0;

char delim[] = " ";

int main()
{
	char command_line[BUFFER_SIZE];
	char *token;

	back:
	printf("$ ");
	if (read_line(command_line, BUFFER_SIZE) <= 0) //입력
		goto back;

	token = strtok(command_line, delim);  //첫 번째 토큰
	int len = strlen(token);

	for (int i = 0;i<len;i++)
	{
		if ('0' <= token[i] && token[i] <= '9')
		{
			num = num * 10 + token[i] - '0';
		}
		else
		{
			if (num > 0) {
				sum = sum + num;
				num = 0;
			}
		}
	}

	while (1)  //그 이후의 토큰
	{
		token = strtok(NULL, delim);
		if (token == NULL) break;
		len = strlen(token);
		if (num != 0)
		{
			sum += num;
			num = 0;
		}


		for (int i = 0;i<len;i++)
		{
			if ('0' <= token[i] && token[i] <= '9')
			{
				num = num * 10 + token[i] - '0';
			}
			else
			{
				if (num > 0) {
					sum = sum + num;
					num = 0;
				}
			}
		}
	}
	printf("모든 정수들의 합 : %d\n", sum);

	return 0;
}
int read_line(char str[], int limit)
{
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit - 1)
			str[i++] = ch;
	str[i] = '\0';

	return i;
}