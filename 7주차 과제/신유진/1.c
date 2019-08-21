//이중 연결리스트
#pragma warning(disable : 4996)
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
int index = 0;

typedef struct node {
	char* word;
	int cnt;
	struct node* next;

}Node;

Node* head = NULL;
Node* word_lists[27] = { NULL };

int add_after(Node *prev, char *item);
void add_first(char *item, int n);
void add_to_ordered_list(char *item, int n);
void print_all();

int main() {
	int m = 0, result = 0;
	char str[MAX];                           //harry에 저장된 단어들
	char* ignore[MAX];
	head = (Node*)malloc(sizeof(Node));

	FILE* fp1 = fopen("harry.txt", "r");
	FILE* fp2 = fopen("ignore.txt", "r");

	while (!feof(fp2)) {
		ignore[m] = malloc(100);
		fscanf(fp2, "%s", ignore[m]);
		m++;
	}

	while (!feof(fp1)) {
		result = 0;
		fscanf(fp1, "%s", str);
		for (int i = 0; i < m; i++) {
			if (strlen(str) <= 2 || strcmp(str, ignore[i]) == 0) {                 
				result = 1;
				break;
			}
		}
		if (result == 0) {					 //연결리스트에 저장할 단어들
			index = str[0] - 'a';
			add_to_ordered_list(str, index);
		}
	}

	print_all();
	fclose(fp1);
	fclose(fp2);
	return 0;
}

void add_first(char *item, int n){
	Node *temp = (Node *)malloc(sizeof(Node));
	temp->word = _strdup(item);
	temp->cnt = 1;
	temp->next = word_lists[n];
	word_lists[n] = temp;
}

int add_after(Node *prev, char *item ){
	if (prev == NULL)							
		return 0;

	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp->word = _strdup(item);
	tmp->cnt = 1;
	tmp->next = prev->next;
	prev->next = tmp;
	return 1;
}

void add_to_ordered_list(char *item, int n) {
	Node* p = word_lists[n];
	Node* q = NULL;
	while (p != NULL && strcmp(item, p->word) >= 0) {
		if (strcmp(item, p->word) == 0) {
			p->cnt++;
			return;
		}
		q = p;
		p = p->next;
	}

	if (p == NULL) {									//empty linked list
	word_lists[n] = (Node*)malloc(sizeof(Node));	
	word_lists[n]->word = strdup(item);
	word_lists[n]->next = NULL;
	word_lists[n]->cnt = 1;
	return;
	}

	 if (q == NULL) {								//first data
		add_first(item, n);
		return;
	 }

	add_after(q, item);								
	return;
}

void print_all() {
	for (int i = 0; i < 27; i++) {
		Node *r = (Node*)malloc(sizeof(Node));
		r = word_lists[i];
		while (r != NULL) {
			printf("%s : %d\n", r->word, r->cnt);
			r = r->next;
		}
	}
}