#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define CAPACITY 100
#define BUFFER_SIZE 30

char* names[CAPACITY];
char* numbers[CAPACITY];
int n = 0;
void add();
void find();
void status();
void remuv();
void load();
void save();
void find_all();
void delete_all();
int main()
{
	char buffer[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		scanf("%s", buffer);

		if (strcmp(buffer, "add") == 0)
			add();
		else if (strcmp(buffer, "find") == 0)
			find();
		else if (strcmp(buffer, "status") == 0)
			status();
		else if (strcmp(buffer, "delete") == 0)
			remuv();
		else if (strcmp(buffer, "save") == 0)
			save();
		else if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "exit") == 0)
			break;
		else if (strcmp(buffer, "findall") == 0)
			find_all();
		else if (strcmp(buffer, "deleteall") == 0)
			delete_all();
	}
	return 0;
}

void add()
{
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	int i = n - 1;
	while (i > 0 && strcmp(names[i], buf1) > 0)
	{
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}

	names[i + 1] = _strdup(buf1);
	numbers[i + 1] = _strdup(buf2);
	n++;

	printf("%s was added successfully.\n", buf1);
}

void find()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
		printf("No person named '%s' exists.\n", buf);
	else
		printf("%s\n", numbers[index]);
}

void status()
{
	for (int i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}

void remuv()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
	{
		printf("No person named '%s' exists.\n", buf);
		return 0;
	}

	int j = index;
	for (; j < n - 1; j++)
	{
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", buf);
}

void load()
{
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE* fp = fopen("datafile.txt", "r");
	if (fp == NULL)
	{
		printf("open failed.\n");
		return 0;
	}
	while (fscanf(fp, "%s", buf1) != EOF)
	{
		fscanf(fp, "%s", buf2);
		names[n] = _strdup(buf1);
		numbers[n] = _strdup(buf2);
		n++;
	}
	fclose(fp);
}

void save()
{
	int i;
	char tmp[BUFFER_SIZE];
	scanf("%s", tmp);
	FILE* fp = fopen("datafile.txt", "w");
	if (fp == NULL)
	{
		printf("open failed.\n");
		return 0;
	}
	for (i = 0; i < n; i++)
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	fclose(fp);
}

int search(char* name)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(name, names[i]) == 0)
			return i;
	}
	return -1;
}

void find_all()
{
	
}

void delete_all()
{

}