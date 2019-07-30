#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 6000

void data_sort(char** data, int* count, int n);


int main() {

	char* data[MAX] = { NULL, };
	int data_num[MAX] = { 0, };
	int index = 0;
	char buffer[50];

	FILE *fp1 = fopen("harry.txt", "r");

	while (!feof(fp1))
	{
		fscanf(fp1, "%s", buffer);
		if (strlen(buffer) >= 6)
		{
			for (int i = 0; i <= index; i++)
			{
				if (i<index && strcmp(buffer, data[i]) == 0)
				{
					data_num[i]++;
					break;
				}
				if (i == index)
				{
					data[i] = strdup(buffer);
					data_num[index]++;
					index++;
					break;
				}
			}
		}
	}
	fclose(fp1);

	data_sort(data, data_num, index);

	FILE *fp2 = fopen("words.txt", "w");

	for (int i = 0; i < index;i++)
		fprintf(fp2, "%s: %d\n", data[i], data_num[i]);
	
	fclose(fp2);

	for (int i = 0; i < index; i++)
		free(data[i]);

	return 0;

}

void data_sort(char** data, int* count, int n) {
	char* dtmp;
	int itmp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp(data[j], data[j + 1]) > 0)
			{
				dtmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = dtmp;

				itmp = *(count + j);
				*(count + j) = *(count + j + 1);
				*(count + j + 1) = itmp;
			}
		}
	}
}