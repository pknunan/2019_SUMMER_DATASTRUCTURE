#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define max 100
int main()
{
	char str[max];
	scanf("%s", &str);

	if (strcmp(str, " ") == 0)
		printf("IP address NULL\n");

	int len = strlen(str);
	if (len > 15 || len < 7) {
		printf("NO\n");
		return 0;
	}

	char delim[] = ".";
	int *token;
	int count = 0;

	token = strtok(str, delim);
	
	while (token != NULL) {
		int num = atoi(token);
		if (num >= 0 && num <= 255)
			count++;
		token = strtok(NULL, delim);
	}

	if (count != 4)
		printf("NO\n");
	else
		printf("YES\n");


	return 0;
}