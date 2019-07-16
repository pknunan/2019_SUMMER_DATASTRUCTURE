#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define MAX 100

int main() {

	char str[MAX];
	scanf("%[^\n]", str);
	int num[MAX] = { 0 };
	int number;
	int n = 0, sum = 0;

	char *token;
	token = strtok(str, " ");
	while (token != NULL) {
		int len = strlen(token);
		for (int i = 0; i < len; i++) {
			if (token[i] >= '0'&&token[i] <= '9') {
				number = token[i] - '0';
				num[n] = num[n] * 10 + number;
			}
			else n++;
			if (i == len - 1)
				n++;
		}
		token = strtok(NULL, " ");
	}
	
	for (int k = 0; k < n; k++) {
		if (num[k] != 0) {
			printf("%d", num[k]);
			printf("+");
			sum += num[k];
		}
	}

	printf("=%d", sum);

	getchar(); getchar();
}