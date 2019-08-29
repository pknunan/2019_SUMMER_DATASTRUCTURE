#ifndef STACKADT_H
#define STACKADT_H
#define	INIT_CAPACITY 100

typedef struct stack_type* Stack;

typedef int Item;

struct stack_type {
	Item* contents;
	int top;
	int size;
};

#endif