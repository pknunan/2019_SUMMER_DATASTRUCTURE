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
int i = 0, j = 0, *index_ptr = NULL;							// i-->다항식의 개수
char buf;
typedef struct term {					//하나의 항을 표현하는 구조체
	int coef;							//계수
	int expo;							//차수
}Term;

typedef struct polynomial {				//하나의 다항식을 표현하는 구조체
	char name;
	int nbr_terms;						//이 다항식을 구성하는 항의 개수
	Term terms[MAX_TERMS];
}Polynomial;

Polynomial polys[MAX];						//여러개의 다항식을 저장하기 위한 배열

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

void create(){											//다항식 정의
	scanf(" %c", &polys[i].name);
	polys[i].terms[0].coef = 0;
	polys[i].terms[0].expo = 0;
	i++;
	polys[i-1].nbr_terms++;											//항의 개수 추가
}

int add(Polynomial poly[]) {
	int c, e, result=0;											//c-> 계수 e->차수

	scanf(" %c", &buf);
	scanf("%d %d", &c, &e);
	if (c == 0) return 0;
	index(buf, &index_ptr);
	j = index_ptr;

	for (int n = 0; n < polys[j].nbr_terms; n++) {
		if (polys[j].terms[n].expo == e) {							//차수가 같은 항이 존재할 때
			polys[j].terms[n].coef += c;
			result = 1;
			break;
		}
		else if ((polys[j].terms[n].expo == 0)) {					//f(x)=0인 상태에서 더할 때
			polys[j].terms[0].coef = c;
			polys[j].terms[0].expo = e;
			result = 1;
			break;
		}
	}
	if(result==0){													//같은 차수가 존재하지 않을 때
		int k = polys[j].nbr_terms;
		polys[j].terms[k].coef = c;
		polys[j].terms[k].expo = e;
		polys[j].nbr_terms++;
	}
}

int index(char poly_name, int *index_ptr) {								//다항식 이름의 인덱스를 반환하는 함수
	for (int j = 0; j < i; j++) {
		if (poly_name == polys[j].name) {
			*index_ptr = j;
			return *index_ptr;
		}
	}
}

void mult() {
	int dub;											//곱해지는 값

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
	return ;														//x에 값을 대입하여 출력
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
		if (polys[j].terms[k].expo == 0) 						//다항식에서 상수가 나오면 멈추기
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