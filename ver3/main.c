#include <stdio.h>
#include <stdlib.h>

#include "sortedlist.h"

int 
main () 
{
	int n ;

	sortedlist_t * l ; 

	l = sortedlist_alloc() ;

	sortedlist_insert(l, 3) ; 
	sortedlist_insert(l, 2) ;
	sortedlist_insert(l, 2) ;
	sortedlist_insert(l, 1) ;

	for (n = 12 ; n >= 0 ; n--) 
		sortedlist_insert(l, n) ;

	int i ;
	for (i = 0 ; i < sortedlist_length(l) ; i++) {
		int e ;
		sortedlist_retrieve(l, i, &e) ;
		printf("%d ", e) ;
	}
	printf("\n") ;

	for (i = 0 ; i <= 13 ; i++) {
		int idx ;
		idx = sortedlist_lookup(l, i) ;
		printf("%d ", idx) ;
	}
	printf("\n") ;

}
