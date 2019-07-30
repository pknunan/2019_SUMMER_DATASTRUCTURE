#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {

	char arr[100];
	int num = 0, state = 0, result;

	scanf("%s", arr);
	char *token=strtok(arr, ".");

	while (token != NULL) {

		if (atoi(token) == 0) {
			printf("No\n");
			state = 1;
			break;
		}
		if ((atoi(token) < 0 || atoi(token) > 255))
		{
			printf("No\n");
			state = 1;
			break;
		}

		token = strtok(NULL, ".");
	}

	if (state == 0)
		printf("Yes\n");

	return 0;
}