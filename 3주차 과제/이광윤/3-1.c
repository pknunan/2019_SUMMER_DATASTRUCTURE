#define _CRT_SECURE_NO_WARNINGS
#define SIZE 100
#include <stdio.h>
#include <string.h>

int main(void)
{
	char str[SIZE];
	fgets(str, sizeof(str), stdin);
	int sum = 0, n = 0, num = 0, real = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			num = str[i] - '0';
			sum = sum * 10 + num;
			if (str[i + 1]<'0' || str[i + 1]>'9')
			{
				real += sum;
				sum = 0;
			}
		}
	}
	printf("%d", real);
	return 0;
}