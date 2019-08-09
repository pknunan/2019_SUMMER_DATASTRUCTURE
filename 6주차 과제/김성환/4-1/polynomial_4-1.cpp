#define _CRT_SECURE_NO_WARNINGS
#include "polynomial_4-1.h"

polynomial polys[MAX] = { 0, };
int n = 0;

void addTerm(char name, char* _c, char* _e) {
	int c = atoi(_c);
	int e = atoi(_e);
	if (c == 0)
		return;
	int curr = 0; // ��� �̵��� ���� �ε���
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

	while (polys[index].nbr_terms != 0 && polys[index].terms[curr].expo > e) // ���� ������ 1���̻��϶�, �߰��ϴ� ���� ������ �ش� ���� �������� ���� ���������� �̵�
	{
		curr++;
	}
	if (curr < polys[index].nbr_terms && polys[index].terms[curr].expo == e) // �߰��Ϸ��� �װ� ���� ������ ���� ������
	{
		polys[index].terms[curr].coef += c; // ����� ���Ѵ�
		if (polys[index].terms[curr].coef == 0) // ����� 0�� �ȴٸ� ��� ���� �ʿ�
		{
			for (int i = curr; i < polys[index].nbr_terms; i++)
			{
				polys[index].terms[i] = polys[index].terms[i + 1]; // �ش� �׺��� 1ĭ�� �������� ����Ʈ
			}
			polys[index].nbr_terms--; // ���� ���� 1 ����
		}
		return;
	}
	//terms[curr]�� ���ο� ���� �߰�
	polys[index].terms[curr].expo = e;
	polys[index].terms[curr].coef = c;
	polys[index].nbr_terms++; //���� ���� 1 ����
}
// polys �迭�� index��° ���׽Ŀ� c*x^e �� �߰�

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
// poly(x)�� ��ȯ

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
// �� 1���� �޾Ƽ� ���� ���

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
// ���׽��� ������ ���

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
// ���δ��� �Է�

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
// ���׽� �迭���� p�� ã�� �� ���

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
// p(x) ���

void polyProcessRun() // ���׽� ���μ��� ����
{
	char buffer[BUFSIZ];
	char copied[BUFSIZ];
	char* command, * arg1, * arg2, * arg3;
	while (1)
	{
		printf("$ ");
		if (readLine(stdin, buffer) <= 0) // ��ɾ� �Է�
			continue;
		strcpy(copied, buffer); // copied�� ���� ��ɾ� ����
		command = strtok(buffer, " "); // ��ɾ� �κ�

		if (strcmp(command, "print") == 0) // printf ���
		{
			arg1 = strtok(NULL, " "); // ���׽� �̸� �κ�
			if (arg1 == NULL) // ����ó��
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

		else if (strcmp(command, "calc") == 0) // calc ���
		{
			arg1 = strtok(NULL, " "); // ���׽� �̸� �ι�
			if (arg1 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " "); // ������ ��
			if (arg2 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			calc(arg1[0], arg2);
		}

		else if (strcmp(command, "create") == 0) // �Լ�����
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			createPoly(arg1[0]);
		}

		else if (strcmp(command, "add") == 0) // ���׽Ŀ� �� �߰�
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			arg3 = strtok(NULL, " ");
			if (arg3 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			addTerm(arg1[0], arg2, arg3);
		}

		else if (strcmp(command, "mult") == 0)
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg1 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			multPoly(arg1[0], arg2);
		}

		else if (strcmp(command, "diff") == 0)
		{
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL || strcmp(arg2, "as") != 0) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			arg3 = strtok(NULL, " ");
			if (arg3 == NULL) { // ����ó��
				printf("Invalid arguments.\n");
				continue;
			}
			diffPoly(arg1[0], arg3[0]);
		}

		else if (strcmp(command, "exit") == 0) // ���� ���
		{
			break;
		}
	}
}
// ���׽� ���μ���

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
// ���׽� name ����

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