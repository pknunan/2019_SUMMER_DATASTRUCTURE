#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define MAX 100

int main()
{
	char str[MAX];
	scanf("%s", str);

	int len = sizeof(str);
	int sum = 0, n = 0, sum_A[MAX] = { 0 };
	for (int i = 0; i < len; i++) {
		if (str[i] >= '0'&&str[i] <= '9') {
			sum = str[i] - '0';
			sum_A[n] = sum_A[n] * 10 + sum;
		}
		else
			n++;
	}

	printf("%d", sum_A);

	return 0;
}