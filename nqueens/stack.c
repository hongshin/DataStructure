#include <stdlib.h>
#include "stack.h"

stack_t * 
create_stack (int capacity, int unit) 
{
	stack_t * stack = (stack_t *) malloc(sizeof(stack_t)) ;
	stack->capacity = capacity ;
	stack->unit = unit ;
	stack->top = 0 ;
	stack->buffer = (char *) calloc(capacity, unit) ;
	return stack ;
}

void
delete_stack (stack_t * stack) 
{
	if (stack->buffer != 0x0)
		free(stack->buffer) ;
	free(stack) ;
}

int 
push (stack_t * stack, void * elem)
{
	if (is_full(stack))
		return 1 ;
	
	memcpy(stack->buffer + stack->top * stack->unit, elem, stack->unit) ;
	stack->top += 1 ;
	return 0 ;
}

int
pop (stack_t * stack, void * elem)
{
	if (is_empty(stack)) 
		return 1 ;
	
	memcpy(elem, stack->buffer + (stack->top - 1) * stack->unit, stack->unit) ;
	stack->top -= 1 ;
	return 0;
}

int 
is_empty (stack_t * stack) 
{
	return (stack->top == 0) ;
}

int 
is_full (stack_t * stack) 
{
	return (stack->top == stack->capacity) ;
}

int
get_size (stack_t * stack) 
{
	return stack->top ;
}

int
get_element (stack_t * stack, int index, void * elem)
{
	if (stack->top <= index)
		return 1 ;

	memcpy(elem, stack->buffer + index * stack->unit, stack->unit) ;
	return 0 ;
}
