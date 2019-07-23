#define _CRT_SECURE_NO_WARNING
#pragma warning(disable : 4996)

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUFFER_SIZE 50000

char *words_list[BUFFER_SIZE];
int words_count[BUFFER_SIZE] = { 0 };
int n;

void load();
void print();
void sort();

int main()
{
	void load();
	void sort();
	void print();

}
void load()
{
	char buffer[BUFFER_SIZE];
	int i = 0;
	FILE *fp = fopen("harry.txt", "r");
	if (fp == NULL){
		printf("OPEN FIAL\n");
		return;
	}
	while (!feof(fp)) {
		fscanf(fp, "%s", buffer);
		if (strlen(buffer) >= 6) {
			words_list[i] = strdup(buffer);
			words_count[i]++;
			n++;i++;
		}
	}
	fclose(fp);
}
void sort()
{
	int k = 0;
	char *temp;
	int count;

	for (int i = 0; i < n; i++) {		
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp(words_list[j],words_list[j + 1])>0) {
				temp = words_list[j];
				words_list[j] = words_list[j + 1];
				words_list[j + 1] = temp;

				count = words_count[j];
				words_count[j] = words_count[j+1];
				words_count[j + 1] = count;
			}
		}
	}

	for (int i = 0;i < n;i++) {		
		if (strcmp(words_list[i], words_list[i + 1]) == 0) {
			k = i;
			while (strcmp(words_list[i], words_list[k + 1]) == 0) {
				words_list[k + 1]=NULL;
				words_count[k]++;
				words_count[k + 1] = 0;
				k++;
			}
			i = k;
		}
	}
}
void print()
{
	FILE *fp = fopen("words.txt", "w");
	if (fp == NULL) {
		printf("OPEN FAIL\n");
		exit(1);
	}
	for (int i = 0;i < n;i++)
		if(words_list[i]!=NULL)
			fprintf(fp, "%s	%d", words_list[i], words_count[i]);

		fclose(fp);
}