#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 80
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

void make_str(FILE * *fpptr);
void align(FILE* fptr);
void add_space(char* ptr);
void remove_space(char* str);
void left_shift(int a, char* str);
void add_word(FILE** fpptr);

char buffer[BUFFER_SIZE + 3];
char tmp[BUFFER_SIZE + 3];

int main()
{
	FILE* fp = fopen("harry.txt", "r");
	FILE* fp2 = fopen("aligned2.txt", "a");
	while (!feof(fp))
	{
		make_str(&fp);

		fprintf(fp2, "%s", buffer);
	}
	fclose(fp);
	fclose(fp2);

	return 0;
}

void make_str(FILE** fpptr)
{
	fgets(buffer, BUFFER_SIZE, *fpptr);
	remove_space(buffer);
	if (!feof(*fpptr) && strlen(buffer) <= BUFFER_SIZE)
		add_word(fpptr);
}

void add_word(FILE** fpptr)
{
	fgets(tmp, BUFFER_SIZE, *fpptr); // 다음행 호출(tmp)
	if (!feof(*fpptr))
		fseek(*fpptr, strlen(tmp) * (-1), SEEK_CUR); // 파일포인터 원위치
	else
		return;
	remove_space(tmp); // 불필요한 공백 삭제

	// (1) 다음행이 \n 라면
	if (tmp[0] == '\n')
	{
		fgets(tmp, BUFFER_SIZE, *fpptr); // 파일포인터 이동
		sprintf(buffer, "%s%s", buffer, tmp);
		return;
	}
	// (2) \n이 아니라면(문자라면)
	else
	{
		char movefp[BUFFER_SIZE];
		char* ptr = strtok(tmp, " \n");
		while (ptr != NULL && strlen(buffer) + strlen(ptr) <= BUFFER_SIZE)
		{
			buffer[strlen(buffer) - 1] = ' ';
			sprintf(buffer, "%s%s\n", buffer, ptr);
			ptr = strtok(NULL, " \n");
			if (ptr != NULL)
			{
				fscanf(*fpptr, "%s", movefp);
			}
			else
			{
				fgets(movefp, BUFFER_SIZE, *fpptr);
			}
		}
		if ((!feof(*fpptr)) && ptr == NULL && strlen(buffer) <= BUFFER_SIZE)
			add_word(fpptr);
		else if (ptr != NULL && strlen(buffer) + strlen(ptr) > BUFFER_SIZE)
		{
			align(*fpptr);
			return;
		}
	}
}

void remove_space(char* str)
{
	for (int i = 0; i < (int)strlen(str); i++)
	{
		if (str[i] == ' ' && i == 0 || str[i] == ' ' && isspace(str[i + 1]))
		{
			left_shift(i, str);
			i--;
		}
	}
}

void left_shift(int a, char* str)
{
	for (int i = a; i <= (int)strlen(str); i++)
	{
		str[i] = str[i + 1];
	}
	str[strlen(str)] = '\0';
}

void align(FILE* fptr)
{
	char* ptr = strchr(buffer, ' ');
	while (strlen(buffer) <= BUFFER_SIZE && !feof(fptr))
	{
		add_space(ptr);
		while (*ptr == ' ')
			ptr += 1;
		ptr = strchr(ptr, ' ');
		if (ptr == NULL)
		{
			ptr = strchr(buffer, ' ');
		}
	}
}

void add_space(char* ptr)
{
	int i = strlen(buffer);
	for (; i >= ptr - buffer; i--)
	{
		buffer[i + 1] = buffer[i];
	}
}