#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

linkedlist_t * 
linkedlist_alloc (int unit) 
{
	linkedlist_t * l = (linkedlist_t *) malloc(sizeof(linkedlist_t)) ;

	l->next = 0x0 ;	
	l->element = malloc(sizeof(int)) ;
	int * u = (int *) l->element ;
	*u = unit ;
	//*((int *) l->element) = unit ;

	return l ;
}

void
linkedlist_free (linkedlist_t * l)
{
	node_t * curr ;
	node_t * next ;

	curr = l ;
	while (curr != 0x0) {
		next = curr->next ;
		free(curr->element) ;
		free(curr) ;
		curr = next ;
	}
}

int 
linkedlist_length (linkedlist_t * l)
{
	int len = 0 ;
	while (l->next != 0x0) {
		l = l->next ; 
		len += 1 ;
	}

	return len ; 
}

void
linkedlist_insert_first (linkedlist_t * l, void * e)
{
	node_t * n = (node_t *) malloc(sizeof(node_t)) ;
	n->element = malloc(*((int *)(l->element))) ;
	memcpy(n->element, e, *((int *)(l->element))) ;

	n->next = l->next ;
	l->next = n ;
}

void
linkedlist_insert_last (linkedlist_t * l, void * e)
{
	int unit = *((int *) l->element) ;
	node_t * n = (node_t *) malloc(sizeof(node_t)) ;
	n->next = 0x0 ;
	n->element = malloc(unit) ;
	memcpy(n->element, e, unit) ;

	while (l->next != 0x0) {
		l = l->next ; 
	}
	l->next = n ;
}

int
linkedlist_remove (linkedlist_t * l, node_t * n)
{
	node_t * prev = l ;
	node_t * curr = l->next ;

	while (curr != 0x0 && curr != n) {
		prev = curr ;
		curr = curr->next ;		
	}
	if (curr == 0x0) 
		return 1 ;

	// curr == n
	prev->next = curr->next ;
	free(curr->element) ;
	free(curr) ;
	return 0 ;
}

int 
linkedlist_remove_first (linkedlist_t * l, void * e)
{
	if (l->next == 0x0)
		return 1 ;

	memcpy(e, l->next->element, *((int *)(l->element))) ;
	linkedlist_remove(l, l->next) ;
	return 0 ;
}

int
linkedlist_remove_last (linkedlist_t * l, void * e)
{
	if (l->next == 0x0)
		return 1 ;

	node_t * n = l ;
	while (n->next != 0x0) {
		n = n->next ;
	}
	// n->next == 0x0 
	memcpy(e, n->element, *((int *)(l->element))) ;

	linkedlist_remove(l, n) ;
	return 0 ;
}

int
linkedlist_get (linkedlist_t * l, int pos, void * e)
{
	if (pos < 0)
		return 1 ;

	int i = 0 ;
	node_t * n = l->next ;
	while (n != 0x0 && i < pos) {
		n = n->next ;
		i++ ;
	}
	if (n == 0x0)
		return 1 ;

	memcpy(e, n->element, *((int *)(l->element))) ;
	return 0 ;
}
