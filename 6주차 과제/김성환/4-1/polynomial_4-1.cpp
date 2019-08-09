#define _CRT_SECURE_NO_WARNINGS
#include "polynomial_4-1.h"

polynomial polys[MAX] = { 0, };
int n = 0;

void addTerm(char name, char* _c, char* _e) {
	int c = atoi(_c);
	int e = atoi(_e);
	if (c == 0)
		return;
	int curr = 0; // 노드 이동을 위한 인덱스
	int index = -1;
	for (int i = 0; i < n; i++)
	{
		if (polys[i].name == name)
			index = i;
	}
	if (index == -1)
	{
		printf("Create %c.\n", name);
		return;
	}

	while (polys[index].nbr_terms != 0 && polys[index].terms[curr].expo > e) // 항의 갯수가 1개이상일때, 추가하는 항의 지수가 해당 항의 지수보다 작지 않을때까지 이동
	{
		curr++;
	}
	if (curr < polys[index].nbr_terms && polys[index].terms[curr].expo == e) // 추가하려는 항과 같은 지수의 항이 있을때
	{
		polys[index].terms[curr].coef += c; // 계수를 더한다
		if (polys[index].terms[curr].coef == 0) // 계수가 0이 된다면 노드 삭제 필요
		{
			for (int i = curr; i < polys[index].nbr_terms; i++)
			{
				polys[index].terms[i] = polys[index].terms[i + 1]; // 해당 항부터 1칸씩 왼쪽으로 시프트
			}
			polys[index].nbr_terms--; // 항의 개수 1 감소
		}
		return;
	}
	//terms[curr]에 새로운 항을 추가
	polys[index].terms[curr].expo = e;
	polys[index].terms[curr].coef = c;
	polys[index].nbr_terms++; //항의 개수 1 증가
}
// polys 배열의 index번째 다항식에 c*x^e 항 추가

int eval(polynomial poly, int x)
{
	int val = 0;
	int curr = 0;

	while (curr < poly.nbr_terms)
	{
		val += (poly.terms[curr].coef * (int)pow(x, poly.terms[curr].expo));
		curr++;
	}

	return val;
}
// poly(x)를 반환

void printTerm(term t)
{
	if (t.coef == -1)
		printf("-");
	else
	{
		if (t.coef != 1)
			printf("%d", t.coef);
	}
	if (t.expo == 0)
	{
		if (t.coef == 1 || t.coef == -1)
			printf("1");
	}
	else
	{
		if (t.expo == 1)
			printf("x");
		else
			printf("x^%d", t.expo);
	}
}
// 항 1개를 받아서 내용 출력

void printPoly(polynomial poly)
{
	printf("%c = ", poly.name);
	int curr = 0;
	while (curr < poly.nbr_terms)
	{
		printTerm(poly.terms[curr]);
		if (curr + 1 == poly.nbr_terms)
			return;
		if (poly.terms[curr + 1].coef > 0)
			printf("+");
		curr++;
	}

}
// 다항식의 내용을 출력

int readLine(FILE* fp, char* str)
{
	int c, i = 0;
	while ((c = fgetc(fp)) != '\n' && c != EOF)
	{
		if (i < BUFSIZ - 1)
			str[i++] = c;
	}
	str[i] = '\0';

	return i;
}
// 라인단위 입력

void print(char p)
{
	int i = 0;
	while (i < n)
	{
		if (polys[i].name == p)
		{
			printPoly(polys[i]);
			printf("\n");
			return;
		}
		i++;
	}
	printf("%c is invalid.\n", p);
}
// 다항식 배열에서 p를 찾아 식 출력

void calc(char p, char* x)
{
	int i = 0;
	int arg = atoi(x);
	while (i < n)
	{
		if (polys[i].name == p)
		{
			printf("%d\n", eval(polys[i], arg));
			return;
		}
		i++;
	}
	printf("%c is invalid.\n", p);
}
// p(x) 출력

void polyProcessRun() // 다항식 프로세스 실행
{
	char buffer[BUFSIZ];
	char copied[BUFSIZ];
	char* command, * arg1, * arg2, * arg3;
	while (1)
	{
		printf("$ ");
		if (readLine(stdin, buffer) <= 0) // 명령어 입력
			continue;
		strcpy(copied, buffer); // copied에 원본 명령어 복사
		command = strtok(buffer, " "); // 명령어 부분

		if (strcmp(command, "print") == 0) // printf 명령
		{
			arg1 = strtok(NULL, " "); // 다항식 이름 부분
			if (arg1 == NULL) // 예외처리
			{
				printf("Invalid arguments.\n");
				continue;
			}
			if (strcmp(arg1, "all") == 0)
			{
				printAll();
				continue;
			}
			print(arg1[0]);
		}

		else if (strcmp(command, "calc") == 0) // calc 명령
		{
			arg1 = strtok(NULL, " "); // 다항식 이름 부문
			if (arg1 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " "); // 대입할 값
			if (arg2 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			calc(arg1[0], arg2);
		}

		else if (strcmp(command, "create") == 0) // 함수생성
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			createPoly(arg1[0]);
		}

		else if (strcmp(command, "add") == 0) // 다항식에 항 추가
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			arg3 = strtok(NULL, " ");
			if (arg3 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			addTerm(arg1[0], arg2, arg3);
		}

		else if (strcmp(command, "mult") == 0)
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg1 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			multPoly(arg1[0], arg2);
		}

		else if (strcmp(command, "diff") == 0)
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL || strcmp(arg2, "as") != 0) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			arg3 = strtok(NULL, " ");
			if (arg3 == NULL) { // 예외처리
				printf("Invalid arguments.\n");
				continue;
			}
			diffPoly(arg1[0], arg3[0]);
		}

		else if (strcmp(command, "exit") == 0) // 종료 명령
		{
			break;
		}
	}
}
// 다항식 프로세스

int createPoly(char name)
{
	for (int i = 0; i < n; i++)
	{
		if (polys[i].name == name)
		{
			printf("Duplicated.\n");
			return 0;
		}
	}
	polys[n++].name = name;
	return 1;
}
// 다항식 name 생성

void multPoly(char name, char* _m)
{
	int m = atoi(_m);
	int index = -1;
	for (int i = 0; i < n; i++)
	{
		if (polys[i].name == name)
		{
			index = i;
			break;
		}
	}
	if (index == -1)
	{
		printf("Create %c.\n", name);
		return;
	}

	for (int i = 0; i < polys[index].nbr_terms; i++)
	{
		polys[index].terms[i].coef *= m;
	}
}

void diffPoly(char f1, char f2)
{
	int index1 = -1;
	for (int i = 0; i < n; i++)
	{
		if (polys[i].name == f1)
		{
			index1 = i;
			break;
		}
	}
	if (index1 == -1)
	{
		printf("Create %c.\n", f1);
		return;
	}
	int index2 = n;
	if (createPoly(f2) == 0)
		return;
	for (int i = 0; i < polys[index1].nbr_terms; i++)
	{
		if (polys[index1].terms[i].expo == 0)
			break;
		polys[index2].terms[i].coef = polys[index1].terms[i].expo * polys[index1].terms[i].coef;
		polys[index2].terms[i].expo = polys[index1].terms[i].expo - 1;
		polys[index2].nbr_terms++;
	}
}

void printAll()
{
	for (int i = 0; i < n; i++)
	{
		int curr = 0;
		printf("%c(x) = ", polys[i].name);
		while (curr < polys[i].nbr_terms)
		{
			printTerm(polys[i].terms[curr]);
			if (curr + 1 == polys[i].nbr_terms)
				break;
			if (polys[i].terms[curr + 1].coef > 0)
				printf("+");
			curr++;
		}
		printf("\n");
	}
}