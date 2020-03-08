#include <stdio.h>
#include <stdlib.h>

#include "arraylist.h"

int 
main () 
{
	arraylist_t * l ; 

	l = arraylist_alloc() ; // ()

	arraylist_insert(l, 1) ; // (1)
	arraylist_insert(l, 2) ; // (1, 2)
	arraylist_insert(l, 3) ; // (1, 2, 3)

	int e ;
	if (arraylist_retrieve(l, 1, &e)) {// e <- 2
		fprintf(stderr, "Error") ;
		return 1 ;
	}
	printf("%d\n", e) ;

	while (arraylist_length(l) > 0) {
		int e ;

		if (arraylist_pop(l, &e)) 
			return 1 ;
		printf("%d ", e) ;
	}
	printf("\n") ;
}
