#pragma warning(disable:4996)
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define CAPACITY 50

int false_count = 0;
int count = 0;

void check_ip();
void read_line(char str[]);

int main(void)
{
	check_ip();
	if (false_count==0&&count==3)
		printf("YES\n");
	else
		printf("NO\n");
	return 0;
}
void check_ip() {
	int number = 0;
	char buffer[CAPACITY];
	char *token; char delim[] = ".";

	read_line(buffer);

	token = strtok(buffer, delim);

	while (token != NULL) {
		number = atoi(token);
		if (number > 255||number<0)
			false_count++;
		token = strtok(NULL, delim);
	}
}
void read_line(char str[])
{
	int i = 0; int ch=0;

	while ((ch = getchar()) != '\n') {
		if (isdigit(ch) != 0)
			str[i++] = ch;
		else if (ch == '.') {
			str[i++] = ch;
			count++;
		}
		else
			false_count++;
	}
	str[i] = '\0';
}