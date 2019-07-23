#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct w {
	char buffer[20];
	int order;
}w;

w *word[1000000];

int StrFind(char *message, int index) {
	int cmp;
	for (int i = 0; i < index; i++)
	{
		if (index == 0) return -1;

		cmp = strcmp(message, word[i]->buffer);
		if (cmp == 0) {
			word[i]->order++;
			return 0;
		}
	}
	return -1;
}

int insert_sort(char *message, int index) {
	int i = 0;
	while (i < index && strcmp(message, word[i]->buffer) > 0)
		i++;
	for (int j = index; j >= i; j--)
		word[j + 1] = word[j];
	return i;
}

int main() {
	FILE *fp1 = fopen("harry.txt", "r");
	char message[20];
	int cmp, index = 0, compare, i, loc = 0;
	while (fscanf(fp1, "%s", message) != EOF) {
		compare = 1;
		if (strlen(message) >= 4) {
			compare = StrFind(message, index);
		}
		if (compare == -1)
		{
			w * New = (w*)malloc(sizeof(w));
			if (index != 0)
				loc = insert_sort(message, index);
			word[loc] = New;
			strcpy(New->buffer, message);
			New->order = 1;
			index++;
		}
	}

	FILE *fp2 = fopen("words.txt", "w");
	for (i = 0; i < index; i++)
		fprintf(fp2, "´Ü¾î: %s , ºóµµ ¼ö : %d\n", word[i]->buffer, word[i]->order);
	fclose(fp1);
	fclose(fp2);
	return 0;
}
