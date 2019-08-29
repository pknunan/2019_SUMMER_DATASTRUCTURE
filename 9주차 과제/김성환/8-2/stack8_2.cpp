#include "stack8_2.h"

static void terminate(const char* message)
{
	printf("%s\n", message);
	exit(1);
}

Stack create()
{
	Stack s = (Stack)malloc(sizeof(struct stack_type));
	if (s == NULL)
		terminate("Error in create: stack could not ne created.");
	s->contents = (Item*)calloc(INIT_CAPACITY, sizeof(Item));
	if (s->contents == NULL) {
		free(s);
		terminate("Error in create: stack could not ne created.");
	}
	s->top = -1;
	s->size = INIT_CAPACITY;
	return s;
}

void stackFree(Stack s)
{
	free(s->contents);
	free(s);
}

bool isEmpty(Stack s)
{
	return (s->top == -1);
}

void push(Stack s, int i)
{
	s->top++;
	if (s->top >= s->size)
	{
		s->size *= 2;
		s->contents = (Item*)realloc(s->contents, sizeof(Item) * (s->size));
		if (s == NULL)
			terminate("Error in create: stack could not ne created.");
	}
	s->contents[s->top] = i;
}

Item pop(Stack s)
{
	if (isEmpty(s))
		terminate("Error in pop: stack is empty");
	s->top--;
	return s->contents[s->top + 1];
}

Item top(Stack s)
{
	if (isEmpty(s))
	{
		terminate("Error in pop: stack is empty");
	}
	return s->contents[s->top];
}