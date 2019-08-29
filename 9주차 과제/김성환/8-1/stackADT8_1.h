#ifndef STACKADT_H
#define STACKADT_H
#define	INIT_CAPACITY 100

typedef struct _contents contents;
typedef struct stack_type* Stack;

typedef contents Item;

struct stack_type {
	Item* contents;
	int top;
	int size;
};
struct _contents {
	int num;
	int data;
};

#endif