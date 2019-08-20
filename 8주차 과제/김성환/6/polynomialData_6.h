#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

typedef struct _term {
	int coef;
	int expo;
	struct _term* next;
}Term;

typedef struct _polynomial {
	char name;
	Term* first;
	int size;
}Polynomial;

#endif