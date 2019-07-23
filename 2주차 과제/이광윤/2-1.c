#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define SIZE 500

int main(void)
{
	char daneo[SIZE], tmp[SIZE];
	FILE* fp1 = fopen("harry.txt", "r");
	FILE* fp2 = fopen("word.txt", "w");
	char* word[SIZE];
	int i = 0;

	while (!feof(fp1))
	{
		fscanf(fp1, "%s", daneo);			//txt파일안의 모든 단어 스캔
		if (strlen(daneo) >= 6)				//6글자 이상의 단어를 word 배열에 복사
		{
			word[i] = _strdup(daneo);
			i++;
		}
	}

	for (int j = 0; j < i - 1; j++)			//i번째와 j번째 비교하여 가나다순서 정렬
	{
		for (int k = j + 1; k < i; k++)
		{
			if (strcmp(word[j], word[k]) > 0)
			{
				strcpy(tmp, word[j]);
				strcpy(word[j], word[k]);
				strcpy(word[k], tmp);
			}
		}
	}

	int a = 0;
	int count[SIZE] = { 0, };
	for (int n = 0; n < i; n++)				//n번째와 다음으로 오는 단어가 같으면 카운트 아니면 파일에 출력
	{
		if (strcmp(word[n], word[n + 1]) == 0)
			count[a]++;
		else if (strcmp(word[n], word[n + 1]) < 0)
		{
			fprintf(fp2, "%s", word[n]);
			fprintf(fp2, "%d\n", count[a]++);
			++a;
		}
	}

	fclose(fp1);
	fclose(fp2);

	return 0;
}