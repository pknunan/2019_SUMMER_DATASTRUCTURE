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
void myremove();
void load();
void save();
void find_all();
void delete_all();
int main() {
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
			myremove();
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

void add() {
	char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
	scanf("%s", buf1);
	scanf("%s", buf2);

	int i = n - 1;
	while (i > 0 && strcmp(names[i], buf1) > 0) {
		names[i + 1] = names[i];
		numbers[i + 1] = numbers[i];
		i--;
	}

	names[i+1] = strdup(buf1);
	numbers[i+1] = strdup(buf2);
	n++;

	printf("%s was added successfully.\n", buf1);
}

void find() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);
	if (index == -1)
		printf("No person named '%s' exists.\n", buf);
	else
		printf("%s\n", numbers[index]);
}

void status() {
	int i;
	for (i = 0; i < n; i++) 
		printf("%s %s\n", names[i], numbers[i]);
	printf("Total %d persons.\n", n);
	
}

void myremove() {
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	int index = search(buf);		//returns -1 if not exists.
	if (index == -1) {
		printf("No person named '%s' exists.\n", buf);
		return ;
	}

	int j = index;
	for (; j < n - 1; j++) {
		names[j] = names[j + 1];
		numbers[j] = numbers[j + 1];
	}
	n--;
	printf("'%s' was deleted successfully.\n", buf);

}

void load() {
	char buf1[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];

	FILE *fp = fopen("datafile.txt", "r");
	if (fp == NULL) {
		printf("open failed.\n");
		return 0;
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
	char tmp[BUFFER_SIZE];

	scanf("%s", tmp);
	FILE *fp = fopen("datafile.txt", "w");
	if (fp == NULL) {
		printf("open failed.\n");
		return 0;
	}
	for (i = 0; i < n; i++) {
		fprintf(fp, "%s %s\n", names[i], numbers[i]);
	}
	fclose(fp);
}

int search(char *name) {
	int i;
	for (i = 0; i < n; i++) {
		if (strcmp(name, names[i]) == 0) {
			return i;
		}
	}
	return -1;
}
void find_all() {
	int count = 0, count_person=0;
	char str[BUFFER_SIZE];
	char name[BUFFER_SIZE];
	char front[BUFFER_SIZE];				//접두어
	scanf("%s", front);
	int length = strlen(front);
	
	for (int i = 0; i < n; i++) {
		strcpy(name, names[i]);

		if (name[0] == front[0]) {
			count = 1;
			for (int j = 1; j < length; j++) {
				if (name[j]== front[j])
					count++;
				
				if (count == length) {
					printf("%s %s\n", name, numbers[i]);
					count_person++;
				}
			}
		}
		else continue;
		
	}
	printf("%d persons found.\n", count_person);

}
void delete_all() {
	int count = 0, count_person = 0, delete_person=0;
	char answer[BUFFER_SIZE];
	char str[BUFFER_SIZE];
	char name[BUFFER_SIZE];
	char front[BUFFER_SIZE];				//접두어
	scanf("%s", front);
	int length = strlen(front);

	for (int i = 0; i < n; i++) {
		strcpy(name, names[i]);

		if (name[0] == front[0]) {
			count = 1;
			for (int j = 1; j < length; j++) {
				if (name[j] == front[j])
					count++;

				if (count == length) {
					printf("do you want to delete '%s'?\n", name);
					scanf("%s", answer);
					if (strncmp(answer,"yes",3)==0) {
						int index = search(front);		//returns -1 if not exists.
						int j = index;
						for (; j < n - 1; j++) {
							names[j] = names[j + 1];
							numbers[j] = numbers[j + 1];
						}
						n--;
						printf("'%s' was deleted.\n", name);
						delete_person++;
					}
					else printf("%s was not deleted.\n", name);
				}
			}
		}
		else continue;
	}
	printf("%s persons deleted.\n", delete_person);
}