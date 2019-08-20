#include "string_tools.h"

int read_line(FILE* fp, char* str, int length){
	int c, i = 0;
	while ((c = fgetc(fp)) != '\n' && c != EOF)
	{
		if (i < length - 1)
			str[i++] = c;
	}
	str[i] = '\0';

	return i;
}

void left_shift(char* str, int i)
{
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
}

void erase_space(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			left_shift(str, i);
			i--;
		}
	}
}