#pragma warning(disable : 4996)
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define BUFFER_SIZE 50

void read_line(char str[]);
int main(void)
{
	int sum = 0;int number = 0;
	char *token;
	char delim[] = "#";
	char integer[BUFFER_SIZE];

	read_line(integer);

	token = strtok(integer, delim);

	while (token != NULL) {
		number = atoi(token);
		sum += number;
		printf("%d\n",number);
		token = strtok(NULL, delim);
	}
	printf("정수들의합 %d",sum);
	return 0;
}
void read_line(char str[])
{
	int ch, i = 0;
	while ((ch = getchar()) != '\n')
		if(isdigit(ch)!=0) 
			str[i++] = ch;
		else if(isdigit(ch)==0)
			str[i++] = '#';
		
	str[i] = '\0';
}