#pragma warning (disable:4996)

#include <stdio.h>
#include <string.h>
#define BUFFER_SIZE 20000

int main() {

	char buffer[BUFFER_SIZE], buffer_l[BUFFER_SIZE];
	int n = 0, sum = 0, rest = 0;

	char *token;

	FILE *fp1 = fopen("harry.txt", "r");
	FILE *fp2 = fopen("aligned.txt", "w");
	while (!feof(fp1))
	{
		fscanf(fp1, "%s", buffer);
		sum += (strlen(buffer) + 1);
		if (sum == 81) {
			fprintf(fp2, "%s", buffer);
			fprintf(fp2, "\n");
			sum = 0;
		}
		else if (sum > 81) {
			sum -= (strlen(buffer) + 1);
			rest = 80 - sum;
			for (int i = 0; i < rest; i++) {
				fscanf(fp2, "%s", buffer_l);
				fprintf(fp2, "%s  ", buffer_l);
			}
			fprintf(fp2, "\n");
			fprintf(fp2, "%s ", buffer);
			sum = 0;
			break;
		}
		else {
			fprintf(fp2, "%s ", buffer);
			continue;
		}

	}
	fclose(fp1);

	return 0;
}