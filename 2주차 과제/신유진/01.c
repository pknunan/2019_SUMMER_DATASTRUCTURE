#include <stdio.h>
#include <string.h>
#define MAX 70000
#define MAX_LEN 20

int main() {
	char str[MAX_LEN];					//한 단어를 한 문자씩 받을 배열
	char tmp[MAX_LEN];
	int tmp_count=0;
	char *words[MAX];					//단어들을 담은 배열
	int count[MAX] = { 0 };				//단어 등장 빈도
	int n = 0;
	int dup = 1;

	FILE *fp = fopen("harry.txt", "r");
	FILE *fp2 = fopen("words.txt", "w");

	while (fscanf(fp, "%s", str) != EOF) {

		if (strlen(str) >= 6) {

			if (n == 0) {						//처음 나온 단어는 무조건 배열에 넣기
				words[n++] = strdup(str);
				continue;
			}

			dup = 1;
			for (int i = 0; i < n; i++) {
				if (strcmp(words[i], str) == 0) {			//str과 기존의 단어가 중복되면
					count[i]++;
					dup = 0;
					break;
				}
			}

			if (dup == 1)								//중복되지 않으면  words 배열에 추가
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
