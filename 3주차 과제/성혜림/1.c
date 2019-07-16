#pragma warning (disable : 4996)
#include <stdio.h>
#include <string.h>
#define MAX 100
#define SIZE 20

int main(void) {

	char str[MAX];
	printf("input str[] : \n");

	gets_s(str, sizeof(str), stdin);

	int k = 0, sum = 0, sum_2 = 0;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] >= '0'&&str[i] <= '9') {
			sum = sum * 10 + str[i] - '0';
			if (str[i + 1]<'0' || str[i + 1]>'9') {
				sum_2 += sum;
				sum = 0;
			}
		}
	}
	printf("The result is %d\n", sum_2);

	getchar(); getchar();
	return 0;
}