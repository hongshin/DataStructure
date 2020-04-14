#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

queue * 
create_queue (int capacity, int unit) 
{
	queue * que = malloc(sizeof(queue)) ;
	que->capacity = capacity ;
	que->unit = unit ;
	que->buffer = calloc(capacity + 1, unit) ;
	que->front = 0 ;
	que->rear = 0 ;
	return que ;
}

void
delete_queue (queue * que) 
{
	if (que->buffer != 0x0)
		free(que->buffer) ;
	free(que) ;
}

int 
enqueue (queue * que, void * elem)
{
	if (is_full(que))
		return 1 ;

	memcpy(que->buffer + ((que->rear) * (que->unit)), elem, que->unit) ;
	que->rear = (que->rear + 1) % (que->capacity + 1) ;
	return 0 ;
}

int
dequeue (queue * que, void * elem)
{
	if (is_empty(que)) 
		return 1 ;
	
	memcpy(elem, que->buffer + que->front * que->unit, que->unit) ;
	que->front = (que->front + 1) % (que->capacity + 1) ;
	return 0;
}

int 
is_empty (queue * que) 
{
	return (que->front == que->rear) ;
}

int 
is_full (queue * que) 
{
	return (((que->rear + 1) % (que->capacity + 1)) == que->front) ;
}

void
print_queue (queue * que, void (* print_element)(void * elem)) 
{
	int i ;
	for (i = que->front ; i != que->rear ; i = (i + 1) % (que->capacity + 1)) {
		printf("[") ;
		print_element(que->buffer + i * que->unit) ;
		printf("] ") ;
	}
	printf("\n") ;
}
