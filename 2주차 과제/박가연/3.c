#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	int col, row, i = 0, j = 0;
	FILE *fp = fopen("tabular.txt", "r");
	FILE *fp2 = fopen("output.txt", "w");
	fscanf(fp, "%d %d", &col, &row);
	char buf[100], buf2[100];
	char *str[10][10];

	while (fscanf(fp, "%s", buf) != EOF)
	{
		if (strcmp(buf, "&") == 0)
		{
			str[i][j] = strdup(" ");
			j++;
			continue;
		}
		fscanf(fp, "%s", buf2);
		if (strcmp(buf, "&") != 0 && strcmp(buf, "\\\\") != 0)
		{
			while (strcmp(buf2, "&") != 0 && strcmp(buf2, "\\\\") != 0)
			{
				sprintf(buf, "%s %s", buf, buf2);
				fscanf(fp, "%s", buf2);
			}
			str[i][j] = strdup(buf);
			j++;
		}
		if (strcmp(buf2, "\\\\") == 0)
		{
			i++;
			j = 0;
		}
	}
	fclose(fp);
	int max = strlen(str[0][0]);
	for (int p = 0; p < col; p++)
	{
		for (int q = 0; q < row; q++)
		{
			if (max < strlen(str[p][q]))
				max = strlen(str[p][q]);
		}
	}
	for (int p = 0; p < col; p++)
	{
		for (int q = 0; q < row; q++)
		{
			int length = (max - strlen(str[p][q]));
			for (int v = 0; v < length; v++)
				strcat(str[p][q], " ");
		}
	}
	for (int p = 0; p < col; p++)
	{
		for (int q = 0; q < row; q++)
			fprintf(fp2, "%s ", str[p][q]);
		fprintf(fp2, "\n");
	}
	fclose(fp2);
	return 0;
}