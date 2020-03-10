#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

int 
main () 
{
	linkedlist_t * l ; 

	l = linkedlist_alloc() ;

	linkedlist_insert(l, 1) ;
	linkedlist_insert(l, 2) ;
	linkedlist_insert(l, 3) ;
	linkedlist_push(l, 0) ;

	int e ;
	if (linkedlist_retrieve(l, 1, &e)) 
		return 1 ;
	printf("%d\n", e) ;

	linkedlist_remove(l, 3) ;
	linkedlist_remove(l, 1) ;

	while (linkedlist_length(l) > 0) {
		int e ;

		if (linkedlist_pop(l, &e)) 
			return 1 ;
		printf("%d ", e) ;
	}
	printf("\n") ;
}
