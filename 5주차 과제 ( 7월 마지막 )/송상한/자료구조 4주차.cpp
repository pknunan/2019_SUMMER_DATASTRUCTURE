#define _crt_secure_no_warnings
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char ip[15];
char *part;
char delim[] = ".";
char *token;

void divide();
int test(char *token_f);

int main()
{

	scanf("%s", ip);
	if (strlen(ip) > 15) {
		printf("NO");
		return 0;
	}
	divide();

	return 0;

}

void divide()
{
	int check = 1;
	token = strtok(ip, delim);
	while (token != NULL) {
		if (strlen(token) > 3) {
			printf("No");
			return;
		}
		if (strlen(token) == 3) {
			check = test(token);
			if (check == 1)
				token = strtok(NULL, delim);
			else {
				printf("No");
				return;
			}
		}
	}
	printf("Yes");
}


int test(char *token_f)
{
	char str[15];
	strcpy(str, token_f);
	if (str[0] == '1')
		return 1;
	else if (str[0] == '2') {
		if (str[1] >= '0' && str[1] <= '5' && str[2] >= '0' && str[2] <= '5')
			return 1;
	}
	else
		return 0;

}