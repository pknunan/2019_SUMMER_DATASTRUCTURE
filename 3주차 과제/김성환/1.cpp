#define _CRT_SECURE_NO_WARNINGS
#define SIZE 10000
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main()
{
	char* str = (char*)malloc(sizeof(char) * SIZE);
	scanf("%[^\n]s", str);

	int sum = 0;
	int tmp = 0;

	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			tmp = str[i] - 48;
			while (str[i+1]!=NULL && (str[i+1] >= 48 && str[i+1] <= 57))
			{
				tmp *= 10;
				tmp += (str[i + 1] - 48);
				i++;
			}
			sum += tmp;
		}
	}

	printf("%d", sum);

	return 0;
}