/*#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#define SIZE 100
#define buffer_size 50

char *name[SIZE];
char *number[SIZE];
int n = 0;

void read();
void find();
void status();
void delete();
void findall();
void deleteall();

int main() {

	char command[buffer_size];
	while (1) {
		printf("$ ");
		scanf("%s", command);
		getchar();

		if (strcmp(command, "read_datafile.txt") == 0)
			read();
		else if (strcmp(command, "find") == 0)
			find();
		else if (strcmp(command, "status") == 0)
			status();
		else if (strcmp(command, "delete") == 0)
			delete();
		else if (strcmp(command, "findall") == 0)
			findall();
		else if (strcmp(command, "deleteall") == 0)
			deleteall();
		else if (strcmp(command, "exit") == 0)
			break;
	}
	getchar(); getchar();
}

void read() {
	char buffer1[SIZE], buffer2[SIZE];
	FILE *fp = fopen("datafile.txt", "r");
	while (!feof(fp)) {
		fscanf(fp, "%s%s", buffer1, buffer2);
		name[n] = strdup(buffer1);
		number[n] = strdup(buffer2);
		n++;
	}
	fclose(fp);
}

void find() {
	char Name[SIZE];
	scanf("%s", Name);

	for (int i = 0; i < n; i++) {
		if (strcmp(name[i], Name) == 0) {
			printf("%s\n", number[i]);
			return;
		}
	}
	printf("No person named '%s' exists.\n", Name);
}

void findall() {
	char Name[SIZE];
	scanf("%s", Name);
	int len = strlen(Name);
	int num = 0;

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < len; k++) {
			if (name[i][k]==Name[k]) {
				if (k == len - 1) {
					printf("%s %s\n", name[i], number[i]);
					num++;
				}
			}
			else break;
		}
	}
	printf("%d person found.\n", num);
}

void status() {
	int num = n;
	for (int i = 0; i < n; i++) {
		if (name[i] == NULL && number[i] == NULL) {
			num--;
			continue;
		}
		printf("%s %s\n", name[i], number[i]);
	}
	printf("Total %d persons.\n", num);
}

void delete() {
	char Name[SIZE];
	scanf("%s", Name);

	for (int i = 0; i < n; i++) {
		if (strcmp(name[i], Name) == 0) {
			name[i] = NULL;
			number[i] = NULL;
			return;
		}
	}
	printf("No person named '%s' exists.\n", Name);
}

void deleteall() {
	char Name[SIZE];
	scanf("%s", Name);
	int len = strlen(Name);
	int num = 0;
	char Q[buffer_size];

	for (int i = 0; i < n; i++) {
		for (int k = 0; k < len; k++) {
			if (name[i][k]== Name[k]) {
				if (k == len - 1) {
					printf("Do you want to delet '%s'?", name[i]);
					scanf("%s", Q);
					if (strcmp(Q, "yes") == 0) {
						printf("%s was deleted.\n", name[i]);
						name[i] = NULL;
						number[i] = NULL;
						num++;
					}
					else printf("%s was not deleted.\n", name[i]);
				}
			}
			else break;
		}
	}
	printf("%d person deleted.\n", num);
}*/