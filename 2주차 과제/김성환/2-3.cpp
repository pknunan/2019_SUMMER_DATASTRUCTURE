#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int max(char*** arr, int j, int n);

int main()
{
	int row, col;
	int n = 0;
	FILE* fp = fopen("tabular.txt", "r");

	fscanf(fp, "%d %d", &row, &col);

	char*** ptr = (char***)malloc(sizeof(char*) * row);
	for (int i = 0; i < row; i++)
		ptr[i] = (char**)malloc(sizeof(char*)*col);

	char buffer[100];
	char tmp[100];

	while (!feof(fp))
	{
		fscanf(fp, "%s", buffer);
		if (buffer[0] == '&')
		{
			ptr[n / col][n % col] = _strdup(" ");
			n++;
			continue;
		}
		strcpy(tmp, buffer);
		fscanf(fp, "%s", buffer);
		while (buffer[0] != '&' && strcmp(buffer, "\\\\") != 0 && !feof(fp))
		{
			sprintf(tmp, "%s %s", tmp, buffer);
			fscanf(fp, "%s", buffer);
		}
		ptr[n / col][n % col] = _strdup(tmp);
		n++;
	}

	int max_lth[10];
	for (int i = 0; i < col; i++)
	{
		max_lth[i] = max(ptr, i, row);
	}

	FILE* fp2 = fopen("output.txt", "w");
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			fprintf(fp2, "%s ", ptr[i][j]);
			for (int k = strlen(ptr[i][j]); k < max_lth[j]; k++)
			{
				fprintf(fp2, " ");
			}
		}
		fprintf(fp2, "\n");
	}
	fclose(fp2);

	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < col; j++)
		{
			free(ptr[i][j]);
		}
		free(ptr[i]);
	}

	free(ptr);

	return 0;
}

int max(char*** arr, int j, int n)
{
	int mv = strlen(arr[0][j]);
	for (int i = 1; i < n; i++)
	{
		mv = (mv > strlen(arr[i][j]) ? mv : strlen(arr[i][j]));
	}

	return mv;
}
