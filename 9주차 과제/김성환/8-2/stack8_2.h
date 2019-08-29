#include "stackADT8_2.h"
#include <stdio.h>
#include <stdlib.h>

static void terminate(const char* message);
Stack create();
void stackFree(Stack s);
bool isEmpty(Stack s);
void push(Stack s, int i);
Item pop(Stack s);
Item top(Stack s);