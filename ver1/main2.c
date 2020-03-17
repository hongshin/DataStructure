#include <stdio.h>
#include <stdlib.h>

#include "sortedlist.h"

int 
main () // testcase
{
	int i ;

	sortedlist_t * l1, *l2, *l3 ; 

	l1 = sortedlist_alloc() ;
	sortedlist_insert(l1, 1) ; 
	sortedlist_insert(l1, 3) ;
	sortedlist_insert(l1, 5) ;
	sortedlist_insert(l1, 7) ;

	l2 = sortedlist_alloc() ;
	sortedlist_insert(l2, 2) ; 
	sortedlist_insert(l2, 4) ;
	sortedlist_insert(l2, 6) ;
	sortedlist_insert(l2, 8) ;

	l3 = sortedlist_merge(l1, l2) ;

	for (i = 0 ; i < sortedlist_length(l3) ; i++) {
		int e ;
		sortedlist_retrieve(l3, i, &e) ;
		printf("%d ", e) ;
	}
	printf("\n") ;

}
