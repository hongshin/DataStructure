#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int
main () 
{
	stack_t * st ;

	double data ;

	st = create_stack(4, sizeof(double)) ;

	data = 11.0 ;	
	push(st, &data) ;

	data = 12.0 ; 
	push(st, &data) ;
	
	data = 13.0 ; 
	push(st, &data) ;
	
	data = 14.0 ; 
	push(st, &data) ;
	
	data = 15.0 ; 
	push(st, &data) ;

	pop(st, &data) ;
	printf("%f\n", data) ;

	delete_stack(st) ;
}
