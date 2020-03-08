#include <stdio.h>
#include <stdlib.h>
#include "arraylist.h"

arraylist_t * 
arraylist_alloc () 
{
	arraylist_t * l ;

	l = (arraylist_t *) malloc(sizeof(arraylist_t)) ;
	
	l->length = 0 ;
	l->capacity = 10 ;
	l->elements = (int *) calloc(l->capacity, sizeof(int)) ;
	return l ;
}

void
arraylist_insert (arraylist_t * l, int e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;	
		l->elements = (int *) realloc(l->elements, l->capacity) ;
	}
	l->elements[l->length] = e ;
	l->length += 1 ;
}

int
arraylist_retrieve (arraylist_t * l, int pos, int * e)
{
	if (l->length <= pos) 
		return 1 ;
	
	*e = l->elements[pos] ;
	return 0 ;
}

int 
arraylist_length (arraylist_t * l)
{
	return l->length ;
}

int 
arraylist_pop (arraylist_t * l, int * e) 
{
	if (l->length == 0)
		return 1 ;

	*e = l->elements[0] ;
	l->length -= 1 ;

	for (int i = 1 ; i <= l->length ; i++) {
		l->elements[i-1] = l->elements[i] ;
	}

	if (l->length * 4 <= l->capacity) {
		l->capacity = l->length * 2 ;
		l->elements = (int *) realloc(l->elements, l->capacity) ;
	}
	return 0 ;
}
