#include "polynomialData_4-1.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

void addTerm(char name, char* c, char* e); // 현재의 항 이전에 노드를 추가
int eval(polynomial poly, int x); // 다항식의 값을 계산
int eval(term term, int x); // 하나의 값을 계산
void printPoly(polynomial poly); // 다항식을 출력
void polyProcessRun(); // 다항식 프로세스 실행
int readLine(FILE* fp, char* str); // 라인단위 입력
void print(char p); // 함수 p를 출력
void calc(char p, char* x); // p(x) 출력
void polyProcessRun(); // 다항식 프로세스 실행
int createPoly(char name);
void multPoly(char name, char* m);
void diffPoly(char f1, char f2);
void printAll();