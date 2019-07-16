#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 80
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void make_str(FILE** fpptr);
void align(FILE* fptr);
void add_space(char* ptr);

char buffer[BUFFER_SIZE+1];
char tmp[BUFFER_SIZE+1];

int main()
{
	FILE* fp = fopen("harry.txt", "r");
	FILE* fp2 = fopen("aligned.txt", "a");
	while (!feof(fp))
	{
		make_str(&fp);
		if (strlen(buffer) < BUFFER_SIZE)
			align(fp);
		
		fprintf(fp2, "%s", buffer);
		if (!feof(fp))
			fprintf(fp2, "\n");
	}
	fclose(fp);
	fclose(fp2);

	return 0;
}

void make_str(FILE** fpptr)
{
	fscanf(*fpptr, "%s", buffer);
	fscanf(*fpptr, "%s", tmp);
	while (strlen(buffer) + strlen(tmp)< 80)
	{
		sprintf(buffer, "%s %s", buffer, tmp);
		fscanf(*fpptr, "%s", tmp);
		if(feof(*fpptr))
			return;
	}
	fseek(*fpptr, strlen(tmp)*(-1), SEEK_CUR);
}

void align(FILE* fptr)
{
	char* ptr = strchr(buffer, ' ');
	while (strlen(buffer) < BUFFER_SIZE && !feof(fptr))
	{
		add_space(ptr);
		while (*ptr == ' ') 
			ptr+=1;
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
	for (; i >= ptr-buffer; i--)
	{
		buffer[i + 1] = buffer[i];
	}
}