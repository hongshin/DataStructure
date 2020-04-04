#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int
main () 
{
	stack * st ;

	int data ;

	st = create_stack(4, sizeof(int)) ;

	data = 11 ;	
	push(st, &data) ;

	data = 12 ; 
	push(st, &data) ;
	
	data = 13 ; 
	push(st, &data) ;
	
	data = 14 ; 
	push(st, &data) ;

	data = 15 ; 
	push(st, &data) ;

	pop(st, &data) ;
	printf("%d\n", data) ;

	delete_stack(st) ;
}
