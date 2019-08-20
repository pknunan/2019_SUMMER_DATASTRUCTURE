#define _CRT_SECURE_NO_WARNINGS
#include "polynomial_6.h"


Polynomial* polys[50] = { NULL, };
int n = 0;

Term* create_term_instance() {
	Term* t = (Term*)malloc(sizeof(Term));
	t->coef = 0;
	t->expo = 0;
	t->next = NULL;
	return t;
}

Polynomial* create_polynomial_instance(char name) {
	Polynomial* ptr_poly = (Polynomial*)malloc(sizeof(Polynomial));
	ptr_poly->name = name;
	ptr_poly->size = 0;
	ptr_poly->first = NULL;
	return ptr_poly;
}

void add_term(int c, int e, Polynomial* poly) {
	if (c == 0)
		return;
	Term* p = poly->first, * q = NULL;
	while (p != NULL && p->expo > e) {
		q = p;
		p = p->next;
	}
	if (p != NULL && p->expo == e) {
		p->coef += c;
		if (p->coef == 0) {
			if (q == NULL)
				poly->first = p->next;
			else
				q->next = p->next;
			poly->size--;
			free(p);
		}
		return;
	}

	Term* term = create_term_instance();
	term->coef = c;
	term->expo = e;
	if (q == NULL) {
		term->next = poly->first;
		poly->first = term;
	}
	else {
		term->next = p;
		q->next = term;
	}
	poly->size++;
}

int eval(Polynomial* poly, int x) {
	int result = 0;
	Term* t = poly->first;
	while (t != NULL) {
		result += eval(t, x);
		t = t->next;
	}
	return result;
}

int eval(Term* term, int x) {
	int result = term->coef;
	for (int i = 0; i < term->expo; i++) {
		result *= x;
	}
	return result;
}

void print_term(Term* t)
{
	if (t->coef == -1)
		printf("-");
	else
	{
		if (t->coef != 1)
			printf("%d", t->coef);
	}
	if (t->expo == 0)
	{
		if (t->coef == 1 || t->coef == -1)
			printf("1");
	}
	else
	{
		if (t->expo == 1)
			printf("x");
		else
			printf("x^%d", t->expo);
	}
}

void print_poly(Polynomial* poly) // 다항식을 출력
{
	printf("%c = ", poly->name);
	Term* curr = poly->first;
	while (curr != NULL)
	{
		print_term(curr);
		if (curr->next == NULL)
			return;
		if (curr->next->coef > 0)
			printf("+");
		curr = curr->next;
	}

}

int readLine(FILE* fp, char* str)
{
	int c, i = 0;
	while ((c = fgetc(fp) )!= '\n' && c != EOF)
	{
		if (i < BUFSIZ - 1)
			str[i++] = c;
	}
	str[i] = '\0';

	return i;
}

void leftShift(char* str, int i)
{
	while (str[i] != '\0')
	{
		str[i] = str[i + 1];
		i++;
	}
}

void eraseSpace(char* str)
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == ' ')
		{
			leftShift(str, i);
			i--;
		}
	}
}

void handle_print(char p)
{
	int i = 0;
	while (polys[i] != NULL)
	{
		if (polys[i]->name == p)
		{
			print_poly(polys[i]);
			printf("\n");
			return;
		}
		i++;
	}
	printf("%c is invalid.\n", p);
}

void handle_calc(char p, char* x)
{
	int i = 0;
	int arg = atoi(x);
	while (polys[i] != NULL)
	{
		if (polys[i]->name == p)
		{
			printf("%d\n", eval(polys[i], arg));
			return;
		}
		i++;
	}
	printf("%c is invalid.\n", p);
}

Polynomial* create_by_add_two_polynomias(char name, char func1, char func2)
{
	int i = 0;
	Polynomial* arg1 = NULL, * arg2 = NULL;
	while (polys[i] != NULL)
	{
		if (polys[i]->name == func1)
			arg1 = polys[i];
		if (polys[i]->name == func2)
			arg2 = polys[i];
		i++;
	}
	if (arg1 == NULL || arg2 == NULL)
	{
		return NULL;
	}
	Polynomial* poly = create_polynomial_instance(name);
	Term* curr = arg1->first;
	while (curr != NULL)
	{
		add_term(curr->coef, curr->expo, poly);
		curr = curr->next;
	}
	curr = arg2->first;
	while (curr != NULL)
	{
		add_term(curr->coef, curr->expo, poly);
		curr = curr->next;
	}
	return poly;
}

int parse_and_add_term(char* expr, int begin, int end, Polynomial* p_poly)
{
	int i = begin;
	int sign_coef = 1, coef = 0, expo = 1;
	if (expr[i] == '+')
		i++;
	else if (expr[i] == '-') {
		sign_coef = -1;
		i++;
	}
	while (i < end && expr[i] >= '0' && expr[i] <= '9') {
		coef = coef * 10 + (int)(expr[i] - '0');
		i++;
	}
	if (coef == 0)
		coef = sign_coef;
	else
		coef *= sign_coef;
	if (i >= end) {
		add_term(coef, 0, p_poly);
		return 1;
	}
	if (expr[i] != 'x')
		return 0;
	i++;
	if (i >= end) {
		add_term(coef, 1, p_poly);
		return 1;
	}
	if (expr[i] != '^')
		return 0;
	i++;
	expo = 0;
	while (i < end && expr[i] >= '0' && expr[i] <= '9') {
		expo = expo * 10 + (int)(expr[i] - '0');
		i++;
	}
	add_term(coef, expo, p_poly);
	return 1;
}

void destroy_polynomial(Polynomial* ptr_poly)
{
	if (ptr_poly == NULL)
		return;
	Term* t = ptr_poly->first, * tmp;
	while (t != NULL) {
		tmp = t;
		t = t->next;
		free(tmp);
	}
	free(ptr_poly);
}

Polynomial* create_by_parse_polynomial(char name, char* body)
{
	Polynomial* ptr_poly = create_polynomial_instance(name);
	int i = 0, begin_term = 0;
	while (i < strlen(body)) {
		if (body[i] == '+' || body[i] == '-')
			i++;
		while (i < strlen(body) && body[i] != '+' && body[i] != '-')
			i++;
		int result = parse_and_add_term(body, begin_term, i, ptr_poly);
		if (result == 0) {
			destroy_polynomial(ptr_poly);
			return NULL;
		}
		begin_term = i;
	}
	return ptr_poly;
}

void insert_polynomial(Polynomial* ptr_poly) {
	for (int i = 0; i < n; i++) {
		if (polys[i]->name == ptr_poly->name) {
			destroy_polynomial(polys[i]);
			polys[i] = ptr_poly;
			return;
		}
	}
	polys[n++] = ptr_poly;
}

void handle_definition(char* expression)
{
	eraseSpace(expression);
	Polynomial* pol = NULL;
	char* f_name = strtok(expression, "="); // 함수이름
	if (f_name == NULL || strlen(f_name) != 1) {
		printf("Unsupported command.\n");
		return;
	}

	char* exp_body = strtok(NULL, "="); // 구성
	if (exp_body == NULL || strlen(exp_body) <= 0) {
		printf("Invalid expression format.\n");
		return;
	}

	if (exp_body[0] >= 'a' && exp_body[0] <= 'z' && exp_body[0] != 'x') {

		char* former = NULL, * later = NULL;

		if (((former = strtok(exp_body, "+")) != NULL) && strlen(former) == 1) // 다항식 덧셈
		{
			later = strtok(NULL, "+"); // 오른쪽
			if (later == NULL || strlen(later) != 1) {
				printf("Invalid expression format.\n");
				return;
			}

			pol = create_by_add_two_polynomias(f_name[0], former[0], later[0]);
		}
		else if (((former = strtok(exp_body, "*")) != NULL) && strlen(former) == 1) // 다항식 곱셈
		{
			char* later = strtok(NULL, "*");
			if (later == NULL || strlen(later) != 1) {
				printf("Invalid expression format.\n");
				return;
			}

			pol = create_by_multiple_two_polynomias(f_name[0], former[0], later[0]); // 두 식을 곱해서 한 식으로
		}

		if (pol == NULL) {
			printf("Invalid expression format.\n");
			return;
		}
		insert_polynomial(pol);
	}
	else {
		pol = create_by_parse_polynomial(f_name[0], exp_body);
		if (pol == NULL) {
			printf("Invalid expression format.\n");
			return;
		}
		insert_polynomial(pol);
	}
}

void process_command()// 다항식 프로세스 실행
{
	char command_line[BUFSIZ];
	char copied[BUFSIZ];
	char* command, * arg1, * arg2;
	while (1)
	{
		printf("$ ");
		if (readLine(stdin, command_line) <= 0)
			continue;
		strcpy(copied, command_line);
		command = strtok(command_line, " ");
		if (strcmp(command, "print") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			handle_print(arg1[0]);
		}
		else if (strcmp(command, "calc") == 0) {
			arg1 = strtok(NULL, " ");
			if (arg1 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			arg2 = strtok(NULL, " ");
			if (arg2 == NULL) {
				printf("Invalid arguments.\n");
				continue;
			}
			handle_calc(arg1[0], arg2);
		}
		else if (strcmp(command, "printall") == 0)
			print_all();
		else if (strcmp(command, "exit") == 0)
			break;
		else {
			handle_definition(copied);
		}
	}
}

void print_all()
{
	for (int i = 0; i < n; i++)
	{
		print_poly(polys[i]);
		printf("\n");
	}
}

Polynomial* create_by_multiple_two_polynomias(char name, char func1, char func2)
{
	int i = 0;
	Polynomial* arg1 = NULL, * arg2 = NULL;
	while (polys[i] != NULL)
	{
		if (polys[i]->name == func1)
			arg1 = polys[i];
		if (polys[i]->name == func2)
			arg2 = polys[i];
		i++;
	}
	if (arg1 == NULL || arg2 == NULL)
	{
		return NULL;
	}
	Polynomial* poly = create_polynomial_instance(name);

	Term* t1 = arg1->first; Term* t2 = arg2->first;
	int coef = 0, expo = 0;

	while (t1 != NULL)
	{
		while (t2 != NULL)
		{
			coef = t1->coef * t2->coef;
			expo = t1->expo + t2->expo;
			add_term(coef, expo, poly);
			t2 = t2->next;
		}
		t1 = t1->next;
		t2 = arg2->first;
	}

	return poly;
}