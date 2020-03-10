#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

linkedlist_t
linkedlist_alloc () 
{
	return 0x0 ;
}

void
linkedlist_push (linkedlist_t * l, int e)
{
	linkedlist_t new_list = (linkedlist_t) malloc(sizeof(node_t)) ;

	new_list->element = e ;
	new_list->tail = *l ;

	*l = new_list ;
}

int
linkedlist_retrieve (linkedlist_t l, int pos, int * e)
{
	int i = 0 ;
	while (l != 0x0) {
		if (i == pos) {
			*e = l->element ;
			return 0 ;
		}
		// i < pos
		i += 1 ;
		l = l->tail ; 
	}

	return 1 ;
}

int 
linkedlist_length (linkedlist_t l)
{
	int i = 0 ;

	while (l != 0x0) {
		i += 1 ;
		l = l->tail ; 
	}
	return i ;
}

int 
linkedlist_pop (linkedlist_t * l, int * e)
{
	if (*l == 0x0)
		return 1 ;

	linkedlist_t tmp ;
	*e = (*l)->element ; //head
	tmp = *l ;
	*l = (*l)->tail ;
	free(tmp) ;
	return 0 ;
}

int
linkedlist_remove (linkedlist_t * l, int e)
{
	linkedlist_t * p ;
	
	p = l ;
	while (*p != 0x0) {
		if ((*p)->element == e) {
			linkedlist_t tmp ;
			tmp = *p ;
			*p = (*p)->tail ; 
			free(tmp) ;
			return 0 ;
		}
		else {
			p = &((*p)->tail) ;
		}
	}
	return 1 ;
}
