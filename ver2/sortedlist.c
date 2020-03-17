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
search (sortedlist_t * l, int e, int begin, int end)
{
	int mid ;

	if (begin == end)
		return begin ;

	mid = (begin + end) / 2 ;

	if (l->elements[mid] < e)
		return search(l, e, mid + 1 , end) ;

	return search(l, e, begin, mid) ;
}

int 
sortedlist_lookup (sortedlist_t * l, int e)
{
	int pos ;

	pos = search(l, e, 0, l->length) ;
	if ((pos < l->length) && (e == l->elements[pos]))
		return pos ;

	return -1 ; 
}

void
sortedlist_insert (sortedlist_t * l, int e)
{
	if (l->length == l->capacity) {
		l->capacity *= 2 ;	
		l->elements = (int *) realloc(l->elements, l->capacity * sizeof(int)) ;
	}

	l->elements[l->length] = e ;

	int i ;
	for (i = l->length - 1 ; i >= 0 ; i--) {
		if (l->elements[i] > l->elements[i + 1]) {
			int t ;
			t = l->elements[i+1] ;
			l->elements[i+1] = l->elements[i] ;
			l->elements[i] = t ;
		}
		else {
			break ;
		}
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
	sortedlist_t * lm ;
	lm = (sortedlist_t *) malloc(sizeof(sortedlist_t)) ;
	lm->length = 0 ;
	lm->capacity = l1->length + l2->length ;
	lm->elements = (int *) calloc(sizeof(int), lm->capacity) ;

	int i ;
	int from, to ;

	from = 0 ;
	for (i = 0 ; i < l2->length ; i++) {
		to = search(l1, l2->elements[i], 0, l1->length) ;

		memcpy(	(void *)(lm->elements + lm->length), 
				(void *)(l1->elements + from), 
				sizeof(int) * (to - from)) ;
		lm->length += to - from ;
		from = to ;

		lm->elements[lm->length] = l2->elements[i] ;
		lm->length += 1 ;
	}
	memcpy(	(void *)(lm->elements + lm->length), 
			(void *)(l1->elements + from), 
			sizeof(int) * (l1->length - from)) ;

	lm->length += l1->length - from ;

	return lm ;
}
