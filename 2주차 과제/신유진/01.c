#include <stdio.h>
#include <string.h>
#define MAX 70000
#define MAX_LEN 20

int main() {
	char str[MAX_LEN];					//�� �ܾ �� ���ھ� ���� �迭
	char tmp[MAX_LEN];
	int tmp_count=0;
	char *words[MAX];					//�ܾ���� ���� �迭
	int count[MAX] = { 0 };				//�ܾ� ���� ��
	int n = 0;
	int dup = 1;

	FILE *fp = fopen("harry.txt", "r");
	FILE *fp2 = fopen("words.txt", "w");

	while (fscanf(fp, "%s", str) != EOF) {

		if (strlen(str) >= 6) {

			if (n == 0) {						//ó�� ���� �ܾ�� ������ �迭�� �ֱ�
				words[n++] = strdup(str);
				continue;
			}

			dup = 1;
			for (int i = 0; i < n; i++) {
				if (strcmp(words[i], str) == 0) {			//str�� ������ �ܾ �ߺ��Ǹ�
					count[i]++;
					dup = 0;
					break;
				}
			}

			if (dup == 1)								//�ߺ����� ������  words �迭�� �߰�
				words[n++] = strdup(str);

			for (int i = 0; i < n; i++) {
				for (int j = i + 1; j < n; j++) {
					if (strcmp(words[i], words[j]) > 0) {
						strcpy(tmp, words[i]);
						strcpy(words[i], words[j]);
						strcpy(words[j], tmp);
						tmp_count = count[j];
						count[j] = count[i];
						count[i] = tmp_count;
					}
				}
			}
		}
	}

	for (int i = 0; i < n; i++)
		fprintf(fp2, "%s: %d\n", words[i], count[i] + 1);

	fclose(fp);
	fclose(fp2);

	return 0;
}
