#pragma warning (disable : 4996)
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define CAPACITY 100
#define BUFFER_SIZE 20

char *names[CAPACITY];
char *numbers[BUFFER_SIZE];
int n = 0;

void add();
void find();
int search(char *name);
void findall();
void status();
void remove_2();
void deleteall();
void load();
void save();

int main_2(void) {

	char command[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", command);

		if (strcmp(command, "read") == 0)
			load();
		else if (strcmp(command, "add") == 0)
			add();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delite") == 0)
			remove_2();
		else if (strcmp(command, "findall") == 0)
			findall();
		else if (strcmp(command, "deleteall") == 0)
			deleteall();
		else if (strcmp(command, "save") == 0)
			save();
		else if (strcmp(command, "exit") == 0)
			break;
	}
	getchar(); getchar();
	return 0;
}
void load() {
	char fileName[BUFFER_SIZE];
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	scanf("%s", fileName);

	FILE*fp = fopen(fileName, "r");
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
	printf("%s was added successfully.\n", buf1);
}
void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
		printf("No person names '%s' exitsts.\n", buf);
	else
		printf("%s\n", numbers[index]);
}
int search(char *name) {
	for (int i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0)
			return i;
	}
	return -1;
}
void status() {
	for (int i = 0; i < n; i++)
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
}
void findall() {
	char buf[BUFFER_SIZE];
	int count = 0;
	scanf("%s", buf);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < strlen(buf); j++) {
			if (buf[j] == names[i][j]) {
				if (j == (strlen(buf) - 1)) {
					printf("%s %s\n", names[i], numbers[i]);
					count++;
				}
			}
			else
				continue;
		}
	}
	if (count == 0)
		printf("No person starting names '%s' exitsts.\n", buf);
	else
		printf("%d persons found.\n", count);
}
void deleteall() {
	char buf[BUFFER_SIZE];
	char answer[BUFFER_SIZE];
	int count = 0,k=0;
	scanf("%s", buf);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < strlen(buf); j++) {
			if (buf[j] == names[i][j]) {
				if (j = (strlen(buf) - 1)) {
					printf("Do you want to delete '%s' ?", names[i]);
					scanf("%s", answer);
					if (answer == 'yes') {
						for (k = i; k < n; k++) {
							names[k] = names[k + 1];
							numbers[k] = numbers[k + 1];
						}
						k--;
						printf("'%s' was deleted.\n", names[i]);
						count++;
					}
					else {
						printf("'%s' was not deleted.\n", names[i]);
					}
				}
			}
		}
	}
	printf("%d persons delteted.\n", count);
}
void remove_2() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);

	int index = search(buf);
	if (index == -1) {
		printf("No person named '%s' exists.\n", buf);
		return;
	}
	for (int j = index; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", buf);
}
void save() {
	char fileName[BUFFER_SIZE];
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp);//as
	scanf("%s", fileName);

	FILE*fp = fopen(fileName, "w");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	for (int i = 0; i < n; i++)
		fprintf(fp, "%s %s\n", names[i], numbers[i]);

	fclose(fp);
}