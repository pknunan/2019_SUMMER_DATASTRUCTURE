#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>

#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[CAPACITY];
int n = 0;

void add();
void find();
void status();
void remove_1();
void load();
void save();
void findall();
void deleteall();
int search(char *name);

int main() {

	char buffer[BUFFER_SIZE];

	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "find") == 0)
			find();
		else if (strcmp(buffer, "add") == 0)
			add();
		else if (strcmp(buffer, "status") == 0)
			status();
		else if (strcmp(buffer, "findall") == 0)
			findall();
		else if (strcmp(buffer, "deleteall") == 0)
			deleteall();
		else if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "save") == 0)
			save();
		else if (strcmp(buffer, "exit") == 0)
			break;
	}

	return 0;
}

void add() {
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
	printf("%s was added successfully/\n", buf1);
}
void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
		printf("No person named '%s' exists. \n", buf);
	else
		printf("%s\n", numbers[index]);
}
void status() {
	int i;
	for (i = 0; i < n; i++)
		printf("%s  %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}
void findall() {
	char buf[BUFFER_SIZE];
	int length, count = 0, pers = 0;
	scanf("%s", buf);
	for (int i = 0; i < n; i++) {
		length = strlen(buf);
		for (int j = 0; j < length; j++) {
			if (names[i][j] == buf[j])
				count++;
		}
		if (count == length) {
			printf("%s  %s\n", names[i], numbers[i]);
			pers++;
		}
		count = 0;
	}
	printf("%d person found.\n", pers);
}
void deleteall() {
	char buf[BUFFER_SIZE], input[BUFFER_SIZE];
	int length, count = 0, pers = 0;
	scanf("%s", buf);
	for (int i = 0; i < n; i++) {
		length = strlen(buf);
		for (int j = 0; j < length; j++) {
			if (names[i][j] == buf[j])
				count++;
		}
		if (count == length) {
			pers++;
			printf("Do you want to delete '%s' ?", names[i]);
			scanf("%s", input);
			if (strcmp(input, "yes") == 0)
			{
				int j = i;
				for (; j < n - 1; j++) {
					names[j] = names[j + 1];
					numbers[j] = numbers[j + 1];
				}
				printf("%s was deleted.\n", names[i]);
			}
			else
				printf("%s was not deleted.\n", names[i]);
		}
		count = 0;
	}
	printf("%d person deleted.\n", pers);
}
void remove_1() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	int j = index;
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
}
void load() {
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while ((fscanf(fp, "%s", buf1) != EOF)) {
		fscanf(fp, "%s", buf2);
		names[n] = strdup(buf1);
		numbers[n] = strdup(buf2);
		n++;
	}
	fclose(fp);
}
void save() {
	int i;
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp);
	scanf("%s", fileName);

	FILE *fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open fialed\n");
		return;
	}

	for (i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

int search(char *name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0)
			return i;
	}
	return -1;
}