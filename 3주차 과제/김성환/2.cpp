#define _CRT_SECURE_NO_WARNINGS
#define BUFFER_SIZE 1000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void read();
void save();
void add();
void find();
void status();
void remove();
void findall();
void removeall();
void allfree();
void sort_insertion(char* _name, char* _number);
int BinSearch(char* _name, int s, int m, int e);

int capacity = 10;
char** name = (char**)malloc(sizeof(char*) * capacity);
char** number = (char**)malloc(sizeof(char*) * capacity);
int n = 0;

int main()
{
	char command[10];
	for (int i = 0; ; i++)
	{
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "read") == 0)
			read();
		else if (strcmp(command, "save") == 0)
			save();
		else if (strcmp(command, "add") == 0)
			add();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0)
			remove();
		else if (strcmp(command, "findall") == 0)
			findall();
		else if (strcmp(command, "deleteall") == 0)
			removeall();
		else if (strcmp(command, "exit") == 0)
		{
			allfree();
			return 0;
		}
		else
			printf("Wrong command.\n");
	}
}

void read()
{
	char filename[BUFFER_SIZE];
	char namebuf[BUFFER_SIZE];
	char numbuf[BUFFER_SIZE];

	scanf("%s", filename);
	
	FILE* fp = fopen(filename, "r");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	while (!feof(fp))
	{
		if (n == capacity)
		{
			capacity *= 2;
			name = (char**)realloc(name, sizeof(capacity));
			number = (char**)realloc(number, sizeof(capacity));
		}
		fscanf(fp, "%s %s", namebuf, numbuf);
		name[n] = _strdup(namebuf);
		number[n] = _strdup(numbuf);
		n++;
	}
	fclose(fp);
}

void save()
{
	char filename[BUFFER_SIZE];
	scanf("%s", filename);
	FILE* fp = fopen(filename, "w");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	for (int i = 0; i < n; i++)
	{
		fprintf(fp, "%s %s\n", name[i], number[i]);
	}
	fclose(fp);
}

void add()
{
	char _name[BUFFER_SIZE];
	char _number[BUFFER_SIZE];
	scanf("%s %s", _name, _number);
	sort_insertion(_name, _number);
}

void sort_insertion(char* _name, char* _number)
{
	for (int i = n - 1; i >= 0; i--)
	{
		if (n == capacity)
		{
			capacity *= 2;
			name = (char**)realloc(name, sizeof(capacity));
			number = (char**)realloc(number, sizeof(capacity));
		}
		if (strcmp(_name, name[i]) == -1)
		{
			name[i + 1] = name[i];
			number[i + 1] = number[i];
		}
		else
		{
			name[i + 1] = _strdup(_name);
			number[i + 1] = _strdup(_number);
			break;
		}
	}
	n++;
	printf("%s was added successfully.\n", _name);
}

void find()
{
	char _name[BUFFER_SIZE];
	scanf("%s", _name);
	int index = BinSearch(_name, 0, n/2, n-1);
	if (index == -1)
		printf("No Person named '%s' exists.\n", _name);
	else
		printf("%s\n", number[index]);
}

int BinSearch(char* _name, int s, int m ,int e)
{
	if (s == e)
	{
		if (strcmp(_name, name[s]) == 0)
			return s;
		else
			return -1;
	}
	if (strcmp(_name, name[m]) == -1)
		return BinSearch(_name, s, (s+m) / 2, m-1);
	else if (strcmp(_name, name[m]) == 1)
		return BinSearch(_name, m + 1, (m+1+e) / 2, e);
	else
		return m;
}

void status()
{
	for (int i = 0; i < n; i++)
	{
		printf("%s %s\n", name[i], number[i]);
	}
	printf("Total %d persons.\n", n);
}

void remove()
{
	char _name[BUFFER_SIZE];
	scanf("%s", _name);
	int index = BinSearch(_name, 0, n / 2, n);
	if (index == -1)
	{
		printf("No person name %s exists.\n", _name);
		return;
	}

	for (int i =  index; i < n-1; i++)
	{
		name[i] = name[i + 1];
		number[i] = number[i + 1];
	}
	n--;
	printf("%s was deleted successfully.\n", _name);
}

void findall()
{
	char _name[BUFFER_SIZE];
	scanf("%s", _name);
	int cnt = 0;
	char* ptr;
	for (int i = 0; i < n; i++)
	{
		ptr = strstr(name[i], _name);
		if (ptr != NULL && ptr==name[i])
		{
			printf("%s %s\n", name[i], number[i]);
			cnt++;
		}
	}
	printf("%d persons found.\n", cnt);
}

void removeall()
{
	char _name[BUFFER_SIZE];
	char ack[10];
	scanf("%s", _name);
	int cnt = 0;
	char* ptr;
	for (int i = 0; i < n; i++)
	{
		ptr = strstr(name[i], _name);
		if (ptr != NULL && ptr == name[i])
		{
			printf("Do you want to delete '%s'? ", name[i]);
			scanf("%s", ack);
			if(strcmp(ack, "yes") == 0)
			{
				for (int j = i; j < n - 1; j++)
				{
					name[j] = name[j + 1];
					number[j] = number[j + 1];
				}
				cnt++;
				printf("%s was deleted.\n", _name);
			}
		}
	}
	printf("%d persons deleted.\n", cnt);
	n -= cnt;
}

void allfree()
{
	for (int i = 0; i < n; i++)
	{
		free(name[i]);
		free(number[i]);
	}
	free(name);
	free(number);
}