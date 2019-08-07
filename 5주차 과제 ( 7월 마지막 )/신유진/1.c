#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#define MAX 100
int main() {
	char str[MAX];
	char delim[] = ".";
	char* token;
	int result = 0;

	printf("IP주소를 입력하시오 : ");
	gets(str);
	token = strtok(str, delim);

	while (token != NULL) {
		int length = strlen(token);
		int digit = convert_to_digit(token);
		if (length > 4 || digit < 0 || digit > 255) {
			printf("NO");
			return 0;;
		}
		token = strtok(NULL, delim);
	}
	printf("YES");
	return 0;
}

int convert_to_digit(char* token) {
	int tmp = 0;
	while (*token != 0) {
		tmp = tmp * 10 + (int)(*token - 48);
		token++;
	}
	return tmp;
}