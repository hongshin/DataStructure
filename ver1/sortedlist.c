#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sortedlist.h"


sortedlist_t * 
sortedlist_alloc () 
{
	sortedlist_t * l ;

	l = (sortedlist_t *) malloc(sizeof(sortedlist_t)) ;
	
	l->length = 0 ;
	l->capacity = 10 ;
	l->elements = (int *) calloc(l->capacity, sizeof(int)) ;
	return l ;
}

int 
sortedlist_lookup (sortedlist_t * l, int e)
{
	int i ;

	for (i = 0 ; i < l->length ; i++) {
		if (l->elements[i] == e)
			return i ; 
	}
	return -1 ; 
}

void
sortedlist_insert (sortedlist_t * l, int e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;
		l->elements = (int *) realloc(l->elements, sizeof(int) * l->capacity) ;
	}

	/*
	int i, n ;
	for (i = 0 ; l->elements[i] <= e && i < l->length ; i++) ;
	for (n = l->length - 1 ; n > i ; n--) 
		l->elements[n+1] = l->elements[n] ;
	l->elements[i] = e ;
	*/

	int i ;
	l->elements[l->length] = e ;
	i = l->length - 1 ;
	while (i >= 0 && !(l->elements[i] < l->elements[i+1])) {
		int tmp ;
		tmp = l->elements[i] ;
		l->elements[i] = l->elements[i+1] ;
		l->elements[i+1] = tmp ;
		i-- ;
	}

	l->length += 1 ;
}

int
sortedlist_retrieve (sortedlist_t * l, int pos, int * e)
{
	if (l->length <= pos) 
		return 1 ;
	
	*e = l->elements[pos] ;
	return 0 ;
}

int 
sortedlist_length (sortedlist_t * l)
{
	return l->length ;
}

int 
sortedlist_pop (sortedlist_t * l, int * e) 
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

int 
sortedlist_remove (sortedlist_t * l, int e)
{
	int p ;
	p = sortedlist_lookup(l, e) ;
	if (p == -1)
		return 1 ;

	l->length -= 1 ;
	while (p < l->length) {
		l->elements[p] = l->elements[p + 1] ;
		p += 1 ;
	}
	return 0 ;
}

sortedlist_t *
sortedlist_merge (sortedlist_t * l1, sortedlist_t * l2)
{
	sortedlist_t * lm = 0x0 ;

	lm = (sortedlist_t *) malloc(sizeof(sortedlist_t)) ;
	lm->capacity = l1->length + l2->length ;
	lm->length = l1->length + l2->length ;
	lm->elements = (int *) calloc(lm->capacity, sizeof(int)) ;

	memcpy((void *)lm->elements, (void *)l1->elements, sizeof(int) * l1->length) ;
	memcpy((void *)(lm->elements + l1->length), (void *)(l2->elements), sizeof(int) * l2->length) ;

	int i ;
	for (i = l1->length ; i < l1->length + l2->length ; i++) {
		int p ;
		p = i ; 
		while ((0 < p) && (!(lm->elements[p - 1] < lm->elements[p]))) {
			int t ;
			t = lm->elements[p-1] ;
			lm->elements[p-1] = lm->elements[p] ;
			lm->elements[p] = t ;
			p-- ;
		}
	}

	return lm ;
}
