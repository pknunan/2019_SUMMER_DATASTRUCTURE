#include "polynomialData_4-1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void addTerm(char name, char* c, char* e); // ������ �� ������ ��带 �߰�
int eval(polynomial poly, int x); // ���׽��� ���� ���
int eval(term term, int x); // �ϳ��� ���� ���
void printPoly(polynomial poly); // ���׽��� ���
void polyProcessRun(); // ���׽� ���μ��� ����
int readLine(FILE* fp, char* str); // ���δ��� �Է�
void print(char p); // �Լ� p�� ���
void calc(char p, char* x); // p(x) ���
void polyProcessRun(); // ���׽� ���μ��� ����
int createPoly(char name);
void multPoly(char name, char* m);
void diffPoly(char f1, char f2);
void printAll();