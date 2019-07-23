#pragma warning (disable : 4996)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#define buffer_size 1000

void read_line(char str[], int limit);
void jungsu(char str1[], int i);

int main(void) {

	char line[buffer_size];//한 라인 통채로 읽는다
	char *command;

	read_line(line, buffer_size);
	jungsu(line, buffer_size);

	return 0;
}

void read_line(char str[], int limit) {
	int ch, i = 0;

	while ((ch = getchar()) != '\n')
		if (i < limit - 1)
			str[i++] = ch;
	str[i] = '\0';

	return;
}
void jungsu(char str1[], int i)
{
	int num = 0, sum = 0;
	for (i = 0; str1[i] != 0; i++) {
		if (str1[i] >= '0' && str1[i] <= '9') {
			num = num * 10 + str1[i] - '0';
		}
		else
		{
			if (num > 0) {
				sum = sum + num;
				num = 0;
			}
		}
	}
	if (num > 0) sum += num;
	printf("%d", sum);
}
