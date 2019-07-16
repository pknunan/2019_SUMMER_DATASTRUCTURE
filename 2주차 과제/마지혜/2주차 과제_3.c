#pragma warning (disable:4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

int main() {
	int row, col, n = 0;
	int R = 0, C = 0;
	char buffer[MAX];
	char buffer2[MAX];
	char ***ch[MAX];

	FILE* fp = fopen("tabular.txt", "r");
	fscanf(fp, "%d %d", &row, &col);
	while (!feof(fp)) {
		fscanf(fp, "%s", buffer);
		if (buffer[0] == '&') {
			ch[R][C] = _strdup(" ");
			if (C == 3) {
				C = 0;
				R++;
			}
			else C++;
			n++;
			continue;
		}

		fscanf(fp, "%s", buffer2);
		while (buffer2[0] != '&' && strcmp(buffer2, "\\\\") != 0 && !feof(fp)) {
			sprintf(buffer2, "%s %s", buffer, buffer2);
			fscanf(fp, "%s", buffer2);
		}
		ch[R][C] = _strdup(buffer);
		if (C == 3) {
			C = 0;
			R++;
		}
		else C++;
		n++;
	}

	getchar(); getchar();
}
