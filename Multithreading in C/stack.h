#ifndef STACK_H
#define STACK_H
#include "common.h"
struct stack {
	int top;
	int* data;
};
typedef struct stack STACK;
STACK s;

void push(int dat)
{
	if (s.top < max_length){
    ++s.top;
    s.data[s.top] = dat;
	}
	else return;
}
int pop(){
	int temp = s.data[s.top];
	s.data[s.top]  = -1 ;
	--s.top;
	return temp;
}

int is_full(){
	return s.top >= max_length;
}
int is_empty(){
	return s.top <= 0;
}
#endif
