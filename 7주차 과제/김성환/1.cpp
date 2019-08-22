#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define IGSIZE 50

typedef struct _node {
	_node* next;
	char* word;
	int cnt;
} node;

node* word_lists[27] = { NULL, };
char buffer[BUFSIZ];
char ignore[IGSIZE][BUFSIZ];
int ign = 0;
int isIgnore(char* ptr);
void parseWord(char* buffer, int index);
void freeList();
void printAll();

int main()
{
	FILE* fp = fopen("harry.txt", "r");

	FILE* fp2 = fopen("ignore.txt", "r");
	while (!feof(fp2))
		fscanf(fp2, "%s", ignore[ign++]);
	fclose(fp2);

	while (!feof(fp))
	{
		fscanf(fp, "%s", buffer);
		if (strlen(buffer) <= 2 || isIgnore(buffer) == 1) // 두글자 이하 또는 무시하는 단어라면 다음단어 read
			continue;

		// 저장해야하는 단어라면 연결리스트에서 검색
		int index = buffer[0] - 'a';
		parseWord(buffer, index); // 첫글자를 인덱스로 연결리스트배열 분석
	}
	fclose(fp);

	printAll();

	freeList();

	return 0;
}

int isIgnore(char* ptr)
{
	for (int i = 0; i < ign; i++)
	{
		if (strcmp(ignore[i], ptr) == 0)
			return 1;
	}

	return 0;
}

void parseWord(char* buffer, int index)
{
	node* curr = word_lists[index]; // 연결리스트 순회 포인터
	node* prev = NULL;
	while (curr != NULL && strcmp(buffer, curr->word) == 1) //버퍼보다 크거나 같은 단어까지 연결리스트 순회
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL)
		if (strcmp(buffer, curr->word) == 0) // 같은 단어 존재시
		{
			(curr->cnt)++; // 빈도 1증가
			return;
		}

	// 같은 단어가 없다면 노드 추가
	node* add = (node*)calloc(1, sizeof(node));
	add->cnt = 1;
	add->word = _strdup(buffer);
	add->next = NULL;

	if (prev != NULL)
	{
		if (curr == NULL) // 마지막 노드
			curr = add;
		else // 일반적인 경우
		{
			prev->next = add;
			add->next = curr;
		}
		return;
	}

	// 첫번째 노드
	word_lists[index] = add; // 헤드 지정
	add->next = curr; // next 지정
}

void freeList()
{
	for (int i = 0; i < 27; i++)
	{
		if (word_lists[i] != NULL)
		{
			node* curr = word_lists[i];
			node* prev = NULL;
			while (curr != NULL)
			{
				free(curr->word);
				prev = curr;
				curr = curr->next;
				free(prev);
			}
		}
	}
}

void printAll()
{
	for (int i = 0; i < 27; i++)
	{
		if (word_lists[i] != NULL)
		{
			node* curr = word_lists[i];
			while (curr != NULL)
			{
				printf("%s : %d\n", curr->word, curr->cnt);
				curr = curr->next;
			}
		}
	}
}