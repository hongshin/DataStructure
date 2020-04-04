#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

stack * 
create_stack (int capacity, int unit) 
{
	stack * st = malloc(sizeof(stack)) ;
	st->capacity = capacity ;
	st->unit = unit ;
	st->top = 0 ;
	st->buffer = calloc(capacity, unit) ;
	return st ;
}

void
delete_stack (stack * st) 
{
	if (st->buffer != 0x0)
		free(st->buffer) ;
	free(st) ;
}

int 
push (stack * st, void * elem)
{
	if (is_full(st))
		return 1 ;

	memcpy(st->buffer + ((st->top) * (st->unit)), elem, st->unit) ;
	st->top += 1 ;

	return 0 ;
}

int
pop (stack * st, void * elem)
{
	if (is_empty(st)) 
		return 1 ;
	
	memcpy(elem, st->buffer + (st->top - 1) * st->unit, st->unit) ;
	st->top -= 1 ;
	return 0;
}

int 
is_empty (stack * st) 
{
	return (st->top == 0) ;
}

int 
is_full (stack * st) 
{
	return (st->top == st->capacity) ;
}

int
get_size (stack * st) 
{
	return st->top ;
}

int
get_element (stack * st, int index, void * elem)
{
	if (st->top <= index)
		return 1 ;

	memcpy(elem, st->buffer + index * st->unit, st->unit) ;
	return 0 ;
}

/*********/


int
X (int pos) 
{
	return pos / 8 ;
}

int
Y (int pos) 
{
	return pos % 8 ;
}

int
conflict (stack * st, int next)
{
	int i ; 

	for (i = 0 ; i < st->top ; i++) {
		int present ;
		get_element(st, i, &present) ;
		
		if (X(present) == X(next)) 
			return 1 ;
		if (Y(present) == Y(next)) 
			return 1 ;
		if (X(present) + Y(present) == X(next) + Y(next)) 
			return 1 ;
		if (X(present) - Y(present) == X(next) - Y(next))
			return 1 ;
	}

	return 0 ;
}

int
main () 
{
	stack * sol ;
	sol = create_stack(8, sizeof(int)) ;

	int curr = 0 ;
	while (get_size(sol) < 8) {
		while (curr < 64) {
			if (!conflict(sol, curr)) {
				push(sol, &curr) ;
				curr = 0 ;
				break ;
			}
			curr += 1 ;
		}
		if (curr == 64) {
			pop(sol, &curr) ; 
			curr += 1 ;
		}
	}

	while (!is_empty(sol)) {
		int elem ;
		pop(sol, &elem) ;
		printf("(%d,%d)\n", X(elem), Y(elem)) ;
	}
	return 0 ;
}
