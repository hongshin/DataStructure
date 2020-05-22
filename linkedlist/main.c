#include <stdio.h>
#include <stdlib.h>

#include "linkedlist.h"

int 
main () 
{
	int data ;
	linkedlist_t * l ; 

	l = linkedlist_alloc(sizeof(int)) ;

	data = 1 ;
	linkedlist_insert_last(l, &data) ;

	data = 2 ;
	linkedlist_insert_last(l, &data) ;

	data = 3 ;
	linkedlist_insert_first(l, &data) ;

	data = 4 ;
	linkedlist_insert_first(l, &data) ;

	linkedlist_remove_last(l, &data) ;
	printf("%d\n", data) ;

	linkedlist_get(l, 2, &data) ;
	printf("%d\n", data) ;

	while (linkedlist_length(l) > 0) {
		linkedlist_remove_first(l, &data) ;
		printf("%d ", data) ;
	}
	printf("\n") ;

	linkedlist_free(l) ;
}
