#pragma warning (disable:4996)
#include <stdio.h>
#define MAX 100

int main() {

	char buffer[MAX];
	char *data[4][4];
	int index, i = 0, j = 0;
	FILE *fp1 = fopen("harry.txt", "r");

	while (!feof(fp1))
	{
		fscanf(fp1, "%s", buffer);
		if (buffer=='&')
		{
			data[i][j];
		}
	}
	fclose(fp1);

	return 0;

}