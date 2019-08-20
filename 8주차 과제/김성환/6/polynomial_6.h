#include "PolynomialData_6.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

Term* create_term_instance();
Polynomial* create_polynomial_instance(char name);
void add_term(int c, int e, Polynomial* poly); // ������ �� ������ ��带 �߰�
int eval(Polynomial* poly, int x); // ���׽��� ���� ���
int eval(Term* term, int x); // �ϳ��� ���� ���
void print_term(Term* t);
void print_poly(Polynomial* poly); // ���׽��� ���
void process_command(); // ���׽� ���μ��� ����
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