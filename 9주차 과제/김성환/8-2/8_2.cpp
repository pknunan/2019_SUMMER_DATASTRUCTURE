#define _CRT_SECURE_NO_WARNINGS
#include "stack8_2.h"

#define BUFSIZE 300

int read_line(FILE* fp, char* str, int length) {
	int c, i = 0;
	while ((c = fgetc(fp)) != '\n' && c != EOF)
	{
		if (i < length - 1)
			str[i++] = c;
	}
	str[i] = '\0';

	return i;
}

int main()
{
	Stack s = create();
	char buffer[BUFSIZE];
	int n;
	scanf("%d ", &n);
	while (n--)
	{
		int num = 1;
		read_line(stdin, buffer, BUFSIZE);
		for (int i = 0; buffer[i] != '\0'; i++)
		{
			if (buffer[i] == '(')
			{
				push(s, num);
				printf("%d ", num++);
			}
			else if (buffer[i] == ')')
			{
				printf("%d ", pop(s));
			}
		}
		printf("\n");
	}

	return 0;
}