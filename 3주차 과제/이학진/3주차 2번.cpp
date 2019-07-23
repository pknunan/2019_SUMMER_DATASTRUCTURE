#pragma warning(disable : 4996)

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

void add();
void find();
void status();
void remove();
void load();
void save();
int search(char *name);

void search_all();
int find_all(char str[],int size);

void delete_all();
void find_delete(char str[], int size);

int main()
{
	char buffer[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", buffer);

		if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "add") == 0)
			add();
		else if (strcmp(buffer, "find") == 0)
			find();
		else if (strcmp(buffer, "status") == 0)
			status();
		else if (strcmp(buffer, "remove") == 0)
			remove();
		else if (strcmp(buffer, "save") == 0)
			save();
		else if (strcmp(buffer, "findall") == 0)
			search_all();
		else if (strcmp(buffer, "deleteall") == 0)
			delete_all();
		else if (strcmp(buffer, "exit") == 0)
			break;
	}
	return 0;
}
void load()
{
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failled\n");
		return;
	}
	while ((fscanf(fp, "%s", buf2) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = strdup(buf1);
		numbers[n] = strdup(buf2);
		n++;
	}
	fclose(fp);
}
void save()
{
	int i;
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp);
	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed\n");
		return;
	}
	for (i = 0;i < n;i++)
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	fclose(fp);
}
void add()
{
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	int i = n - 1;
	while (i >= 0 && strcmp(names[i], buf1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = strdup(buf1);
	numbers[i + 1] = strdup(buf2);
	n++;
	printf("%s was added successfully. \n", buf1);
}
void remove()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		printf("NO person named '%s' exists.\n", buf);
		return;
	}
	int j = index;
	for (;j < n - 1;j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully. \n", buf);
}
void find()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
		printf("NO person named '%s' exists.\n", buf);
	else
		printf("%s\n", numbers[index]);
}
int search(char *name) 
{
	int i;
	for (i = 0;i < n;i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}
void status()
{
	int i;
	for (i = 0;i < n;i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}
void search_all()
{
	int size,count;
	char buffer[BUFFER_SIZE];
	scanf("%s", buffer);
	size=strlen(buffer);
	count=find_all(buffer,size);
	printf("%d persons found.\n", count);
}
int find_all(char str[],int size)
{
	int i, number = 0;int count = 0;
	
	char compose[BUFFER_SIZE];
	char compare[BUFFER_SIZE];
	
	for (i = 0;i < size;i++)
		compose[i] = str[i];

	for (i = 0;i < n;i++) {
		strcpy(compare,names[i]);
		for (int j = 0;j < size;j++) {
			if (compose[j] == compare[j])
				number++;
			if (number == size) {
				printf("%s %s\n", names[i],numbers[i]);
				count++;
			}
		}
		number = 0;
	}
	return count;
}
void delete_all()
{
	int size;
	char buffer[BUFFER_SIZE];
	scanf("%s", buffer);
	size = strlen(buffer);
	find_delete(buffer,size);
}
void find_delete(char str[], int size)
{
	int i, number = 0;
	int count = 0;

	char compose[BUFFER_SIZE];
	char compare[BUFFER_SIZE];
	char op[BUFFER_SIZE];

	for (i = 0;i < size;i++)
		compose[i] = str[i];

	for (i = 0;i < n;i++)
	{
		strcpy(compare,names[i]);
		for (int j = 0;j < size;j++)
		{
			if (compose[j] == compare[j])
				number++;
			if (number == size)
			{
				printf("Do you want to delete '%s' ?", names[i]);
				scanf("%s", op);
				if (strcmp(op,"yes")==0)
				{
					printf("%s was deleted.\n", names[i]);
					for (int s = i;s < n - 1;s++)
					{
						names[s] = names[s + 1];
						numbers[s] = numbers[s + 1];
					}
					count++;
				}
				else
					printf("%s was not deleted\n", names[i]);
			}
		}
		number = 0;
	}
	n = n - count;
	printf("%d person deleted \n", count);
}