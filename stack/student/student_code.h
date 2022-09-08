#ifndef SCODE_H
#define SCODE_H

#include <stdint.h>
#include <string.h>
#include <stdlib.h>


// Stack is represented using linked list
struct stack {
    int data;
    struct stack* next;
};


int push(struct stack** s, int x);

void sortStack(struct stack** s);
#endif