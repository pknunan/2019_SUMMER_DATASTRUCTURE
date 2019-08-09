#ifndef POLYDATA_H
#define POLYDATA_H

#define MAX_TERMS 100
#define MAX 100

typedef struct _term {
	int coef;
	int expo;
}term;

typedef struct _polynomial {
	char name;
	int nbr_terms; // ���׽��� �����ϴ� ���� ��
	term* terms[MAX_TERMS];
}polynomial;

#endif