#include "PolynomialData_6.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

Term* create_term_instance();
Polynomial* create_polynomial_instance(char name);
void add_term(int c, int e, Polynomial* poly); // 현재의 항 이전에 노드를 추가
int eval(Polynomial* poly, int x); // 다항식의 값을 계산
int eval(Term* term, int x); // 하나의 값을 계산
void print_term(Term* t);
void print_poly(Polynomial* poly); // 다항식을 출력
void process_command(); // 다항식 프로세스 실행
int readLine(FILE* fp, char* str);
void leftShift(char* str, int i);
void eraseSpace(char* str);
void handle_print(char p);
void handle_calc(char p, char* x);
Polynomial* create_by_add_two_polynomias(char name, char func1, char func2);
int parse_and_add_term(char* expr, int begin, int end, Polynomial* p_poly);
void destroy_polynomial(Polynomial* ptr_poly);
Polynomial* create_by_parse_polynomial(char name, char* body);
void insert_polynomial(Polynomial* ptr_poly);
void handle_definition(char* expression);
void print_all();
Polynomial* create_by_multiple_two_polynomias(char name, char func1, char func2);