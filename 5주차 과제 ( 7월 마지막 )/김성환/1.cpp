#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isValid(char** tok);

int main()
{
	char buf[100];
	char* tok[4];
	scanf("%s", buf);

	char* ptr = strtok(buf, ".");

	int i = 0;
	while (ptr != NULL)
	{
		tok[i] = ptr;
		ptr = strtok(NULL, ".");
		i++;
	}

	if (isValid(tok) == 1)
		printf("Yes\n");
	else
		printf("No\n");

	return 0;
}

int isValid(char** tok)
{
	for (int i = 0; i < 4; i++)
	{
		int j = 0;
		int sum = 0;
		while (tok[i][j]!=NULL)
		{
			if (sum > 0)
				sum *= 10;
			if (tok[i][j] >= 48 && tok[i][j] <= 57)
				sum += tok[i][j] - 48;
			else
				return 0;
			j++;
		}
		if (sum > 255)
			return 0;
	}

	return 1;
}