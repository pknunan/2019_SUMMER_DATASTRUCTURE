#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void data_sort(char** data, int n);

int main() {

	char* data[6000] = { NULL, };
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
					break;
				if (i == index)
				{
					data[i] = strdup(buffer);
					index++;
					break;
				}
			}
		}
	}
	fclose(fp1);

	data_sort(data, index);

	srand((unsigned int)time(NULL));

	char answer[50] = { NULL, };
	char input, guess;
	int random, length, count = 0;

	while (1) {

		random = rand() % index;
		length = strlen(data[random]);
		for (int i = 0; i < length; i++)
			answer[i] = '*';
		for (int i = 0; i < length; i++)
			printf("*");
		printf("\n");
		while (1) {
			printf("Guess an alphabet: ");
			scanf(" %c", &guess);
			for (int i = 0; i < length; i++) {
				if (guess == data[random][i])
					answer[i] = data[random][i];
			}
			printf("%s", answer);
			printf("\n");
			for (int i = 0; i < length; i++)
				if (answer[i] == '*')
					count++;
			if (count == 0)
				break;
			count = 0;
		}
		printf("Try again (y/n) ?");
		scanf(" %c", &input);
		if (input == 'y')
			continue;
		else if (input == 'n')
			break;
	}


	return 0;
}

void data_sort(char** data, int n) {
	char* dtmp;
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (strcmp(data[j], data[j + 1]) > 0)
			{
				dtmp = data[j];
				data[j] = data[j + 1];
				data[j + 1] = dtmp;
			}
		}
	}
}