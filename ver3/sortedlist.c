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
	int begin, end, mid ; 

	begin = 0 ; 
	end = l->length - 1 ;
	while (begin < end) {
		mid = (begin + end) / 2 ;

		if (l->elements[mid] == e) {
			return mid ;
		}
		else if (l->elements[mid] < e) {//  elem[mid+1] <= e <= elem[end] 
			begin = mid + 1 ;
		}
		else /* e < l->elements[mid] */ {
			end = mid - 1 ;
		}
	}
	if (l->elements[begin /*end*/] == e)
		return begin ;
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

	int i1 = 0 , i2 = 0 ;

	while (i1 < l1->length && i2 < l2->length) {
		if (l1->elements[i1] < l2->elements[i2]) {
			lm->elements[lm->length] = l1->elements[i1] ;
			lm->length += 1 ;
			i1 += 1 ;
		}
		else {
			lm->elements[lm->length] = l2->elements[i2] ;
			lm->length += 1 ;
			i2 += 1 ;
		}
	}
	memcpy(	(void *)(lm->elements + lm->length), 
	   		(void *)(l1->elements + i1), 
			sizeof(int) * (l1->length - i1)) ;
	lm->length += l1->length - i1 ;

	memcpy(	(void *)(lm->elements + lm->length), 
	   		(void *)(l2->elements + i2), 
			sizeof(int) * (l2->length - i2)) ;
	lm->length += l2->length - i2 ;

	/*
	while (i1 < l1->length) {
		lm->elements[lm->length] = l1->elements[i1] ;
		lm->length += 1;
		i1 += 1 ;
	}
	while (i2 < l2->length) {
		lm->elements[lm->length] = l2->elements[i2] ;
		lm->length += 1 ;
		i2 += 1 ;
	}
	*/
	return lm ;
}
