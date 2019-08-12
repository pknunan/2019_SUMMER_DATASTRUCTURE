#define _CRT_SECURE_NO_WARNINGES
#pragma warning (disable :4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TERMS 100
#define MAX 100
int add();
void create();
void print();
void mult();
void diff();
void calc();
void print_();
int index(char poly_name, int* index_ptr);
void print_all();
int i = 0, j = 0, *index_ptr = NULL;							// i-->���׽��� ����
char buf;
typedef struct term {					//�ϳ��� ���� ǥ���ϴ� ����ü
	int coef;							//���
	int expo;							//����
}Term;

typedef struct polynomial {				//�ϳ��� ���׽��� ǥ���ϴ� ����ü
	char name;
	int nbr_terms;						//�� ���׽��� �����ϴ� ���� ����
	Term terms[MAX_TERMS];
}Polynomial;

Polynomial polys[MAX];						//�������� ���׽��� �����ϱ� ���� �迭

int main() {
	char command[MAX];
	while (1) {
		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "create") == 0)
			create();

		else if (strcmp(command, "add") == 0)
			add(polys);

		else if (strcmp(command, "mult") == 0)
			mult();

		else if (strcmp(command, "calc") == 0)
			calc();
		
		else if (strcmp(command, "diff") == 0) 
			diff();
		
		else if (strcmp(command, "print") == 0) 
			print();
		
		else if (strcmp(command, "print_all") == 0) 
			print_all();
		
		else if (strcmp(command, "exit") == 0)
			break;
	}
	return 0;
}

void create(){											//���׽� ����
	scanf(" %c", &polys[i].name);
	polys[i].terms[0].coef = 0;
	polys[i].terms[0].expo = 0;
	i++;
	polys[i-1].nbr_terms++;											//���� ���� �߰�
}

int add(Polynomial poly[]) {
	int c, e, result=0;											//c-> ��� e->����

	scanf(" %c", &buf);
	scanf("%d %d", &c, &e);
	if (c == 0) return 0;
	index(buf, &index_ptr);
	j = index_ptr;

	for (int n = 0; n < polys[j].nbr_terms; n++) {
		if (polys[j].terms[n].expo == e) {							//������ ���� ���� ������ ��
			polys[j].terms[n].coef += c;
			result = 1;
			break;
		}
		else if ((polys[j].terms[n].expo == 0)) {					//f(x)=0�� ���¿��� ���� ��
			polys[j].terms[0].coef = c;
			polys[j].terms[0].expo = e;
			result = 1;
			break;
		}
	}
	if(result==0){													//���� ������ �������� ���� ��
		int k = polys[j].nbr_terms;
		polys[j].terms[k].coef = c;
		polys[j].terms[k].expo = e;
		polys[j].nbr_terms++;
	}
}

int index(char poly_name, int *index_ptr) {								//���׽� �̸��� �ε����� ��ȯ�ϴ� �Լ�
	for (int j = 0; j < i; j++) {
		if (poly_name == polys[j].name) {
			*index_ptr = j;
			return *index_ptr;
		}
	}
}

void mult() {
	int dub;											//�������� ��

	scanf(" %c %d", &buf, &dub);
	j = index_ptr;

	index(buf, &index_ptr);
	if (dub == 0) return;

	for (int n = 0; n < polys[j].nbr_terms; n++) {
		polys[j].terms[n].coef *= dub;
	}
}

void calc() {
	int sub, k=0, result=1, sum=0;
	scanf(" %c %d", &buf, &sub);
	index(buf, &index_ptr);
	j = index_ptr;

	for (int n = 0; n < polys[j].nbr_terms; n++) {
		for (int q = 0; q < polys[j].terms[k].expo; q++) {
			result*=sub;
		}
		result *= polys[j].terms[k].coef;
		sum += result;
		result = 1;
		k++;
	}
	printf("%d\n", sum);
	return ;														//x�� ���� �����Ͽ� ���
}

void diff() {
	int k = 0;
	char div;
	char as[3];
	scanf(" %c %s", &buf, as);
	scanf(" %c", &div);
	index(buf, &index_ptr);
	j = index_ptr;

	for (int n = 0; n < polys[j].nbr_terms; n++) {
		polys[i].name = div;
		if (polys[j].terms[k].expo == 0) 						//���׽Ŀ��� ����� ������ ���߱�
			break;
		polys[i].terms[k].coef= polys[j].terms[k].coef * polys[j].terms[k].expo;
		polys[i].terms[k].expo = polys[j].terms[k].expo-1;
		polys[i].nbr_terms++;
		k++;
	}
	i++;
}

void print() {
	scanf(" %c", &buf); 
	index(buf, &index_ptr);
	j = index_ptr;
	print_();
}

void print_all() {
	for (int n = 0; n < i; n++) {
		printf("%c = ", polys[n].name);
		print_();
		j++;
	}
}

void print_() {
	for (int n = 0; n < polys[j].nbr_terms; n++) {
		if (polys[j].terms[n].expo == 1)
			printf("%dx ", polys[j].terms[n].coef);

		else if (polys[j].terms[n].expo == 0)
			printf("%d ", polys[j].terms[n].coef);

		else
			printf("%dx^%d ", polys[j].terms[n].coef, polys[j].terms[n].expo);
	}
	printf("\n");

}