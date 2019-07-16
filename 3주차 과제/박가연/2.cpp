#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[CAPACITY];
int index[BUFFER_SIZE];
int n = 0, cnt=0;
void add();
void find();
void findall();
void status();
void remove();
void removeall();
void load();
void save();
int search(char *buf);
int searchall(char *buf);
int main(void)
{
	char buffer[BUFFER_SIZE];

	while (1)
	{
		cnt = 0;
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "add") == 0)
			add();
		else if (strcmp(buffer, "find") == 0)
			find();
		else if (strcmp(buffer, "findall") == 0)
			findall();
		else if (strcmp(buffer, "status") == 0)
			status();
		else if (strcmp(buffer, "delete") == 0)
			remove();
		else if (strcmp(buffer, "deleteall") == 0)
			removeall();
		else if (strcmp(buffer, "save") == 0)
			save();
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
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	while (fscanf(fp, "%s", buf1) != EOF)
	{
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

	scanf("%s", tmp); //as
	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "w");
	if (fp == NULL)
	{
		printf("Open failed.\n");
		return;
	}
	for (i = 0; i < n; i++)
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	fclose(fp);
}
void add()
{
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	int i = n - 1;
	while (i >= 0 && strcmp(names[i], buf1) > 0)
	{
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}
	names[i + 1] = strdup(buf1);
	numbers[i + 1] = strdup(buf2);

	n++;
	printf("%s was added successfully.\n", buf1);
}
void remove()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1)
	{
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	int j = index;
	for (; j < n - 1; j++)
	{
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully. \n", buf);
}
void removeall ()
{
	char buf[BUFFER_SIZE];
	char answer[100];
	int k = 0;
	scanf("%s", buf);

	int index0 = searchall(buf);
	if (index0 == -1)
	{
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	for (int i = 0; i < cnt; i++)
	{
		char name[100];
		strcpy(name , names[index[i]]);
		printf("Do you want to delete '%s' ? ", name);
		scanf("%s", answer);
		if (strcmp(answer, "yes") == 0)
		{
			int j = index[i];
			for (; j < n - 1; j++)
			{
				names[j] = names[j + 1];
				numbers[j] = numbers[j + 1];
			}
			n--;
			k++;
			printf("'%s' was deleted\n", name);
		}
		else
			printf("'%s' was not deleted.\n", name);
	}
	printf("%d person deleted. \n", k);
}
void find()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index0 = search(buf);
	if (index0 == -1)
		printf("No person named '%s' exists.\n", buf);
	else
		printf("%s\n", numbers[index0]);
}
void findall()
{
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index0 = searchall(buf);
	if (index0 == -1)
	{
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	for (int i = 0; i < cnt; i++)
		printf("%s %s\n", names[index[i]], numbers[index[i]]);
	printf("%d persons found\n", cnt);		
}
int search(char *buf)
{
	for (int i = 0; i < n; i++)
	{
		if (strcmp(buf, names[i]) == 0)
			return i;
	}
	return -1;
}
int searchall(char *buf)
{
	int chk=0, k=0;
	for (int i = 0; i < n; i++)
	{
		if (strncmp(buf, names[i], strlen(buf)) == 0)
		{
			chk = 1;
			index[k++] = i;
		}	
	}
	cnt = k;
	if (chk == 0)
		return -1;
	else
		return 0;
}
void status()
{
	for (int i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d person.\n", n);
}