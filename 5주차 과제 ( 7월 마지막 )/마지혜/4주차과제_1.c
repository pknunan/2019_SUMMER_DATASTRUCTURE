#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define MAX 100

int definestr(char str);
void N();
void Y();

int main() {

	char str[MAX];
	gets_s(str, MAX);

	int sum = 0, count = 0;
	int len = strlen(str);

	if (str[0] == '.' || str[len - 1] == '.') {
		N();
		getchar(); getchar();
		return 0;
	}

	for (int i = 0; i < len; i++) {
		if (definestr(str[i])==2) {
			N();
			break;
		}
		else {
			if (definestr(str[i]) == 0) {
				sum = sum * 10 + str[i] - '0';
				if (sum > 255) {
					N();
					break;
				}
				if (str[i + 1] == '.')
					count++;
				if (i == len - 1)
					count++;
			}
			else {
				if (str[i + 1] == '.') {
					N();
					break;
				}
				sum = 0;
			}
		}
		if (i == len - 1) {
			if (count == 4)
				Y();
			else N();
		}
	}

	getchar(); getchar();
	return 0;
}

int definestr(char str) {
	if (str >= '0' && str <= '9')
		return 0;
	else if (str == '.')
		return 1;
	return 2;
}

void N() {
	printf("NO");
}

void Y() {
	printf("YES");
}