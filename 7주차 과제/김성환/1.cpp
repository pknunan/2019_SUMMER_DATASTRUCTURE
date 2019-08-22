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
		if (strlen(buffer) <= 2 || isIgnore(buffer) == 1) // �α��� ���� �Ǵ� �����ϴ� �ܾ��� �����ܾ� read
			continue;

		// �����ؾ��ϴ� �ܾ��� ���Ḯ��Ʈ���� �˻�
		int index = buffer[0] - 'a';
		parseWord(buffer, index); // ù���ڸ� �ε����� ���Ḯ��Ʈ�迭 �м�
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
	node* curr = word_lists[index]; // ���Ḯ��Ʈ ��ȸ ������
	node* prev = NULL;
	while (curr != NULL && strcmp(buffer, curr->word) == 1) //���ۺ��� ũ�ų� ���� �ܾ���� ���Ḯ��Ʈ ��ȸ
	{
		prev = curr;
		curr = curr->next;
	}

	if (curr != NULL)
		if (strcmp(buffer, curr->word) == 0) // ���� �ܾ� �����
		{
			(curr->cnt)++; // �� 1����
			return;
		}

	// ���� �ܾ ���ٸ� ��� �߰�
	node* add = (node*)calloc(1, sizeof(node));
	add->cnt = 1;
	add->word = _strdup(buffer);
	add->next = NULL;

	if (prev != NULL)
	{
		if (curr == NULL) // ������ ���
			curr = add;
		else // �Ϲ����� ���
		{
			prev->next = add;
			add->next = curr;
		}
		return;
	}

	// ù��° ���
	word_lists[index] = add; // ��� ����
	add->next = curr; // next ����
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