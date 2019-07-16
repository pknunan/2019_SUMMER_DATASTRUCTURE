#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define CAPACITY 100
int main(void)
{
	char str[CAPACITY];
	int digit[CAPACITY];
	int	k=0, sum=0;
	gets_s(str, CAPACITY);
	for (int i = 0; i < strlen(str); i++)
	{
		if (isdigit(str[i]) != 0)
		{
			int j = i+1;
			digit[k] = (int)str[i]-48;
			while (isdigit(str[j]) != 0)
			{
				digit[k] = (digit[k] * 10) + ((int)str[j] - 48);
				j++;
			}
			k++;
			i = j;
		}
	}
	for (int i = 0; i < k; i++)
		sum += digit[i];
	printf("%d\n", sum);
	return 0;
}