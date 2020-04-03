#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"

int
X (int pos) 
{
	return pos / 8 ;
}

int
Y (int pos) 
{
	return pos % 8 ;
}

int
conflict (stack * st, int next)
{
	int i ; 

	for (i = 0 ; i < st->top ; i++) {
		int present ;
		get_element(st, i, &present) ;
		
		if (X(present) == X(next)) 
			return 1 ;
		if (Y(present) == Y(next)) 
			return 1 ;
		if (X(present) + Y(present) == X(next) + Y(next)) 
			return 1 ;
		if (X(present) - Y(present) == X(next) - Y(next))
			return 1 ;
	}

	return 0 ;
}

int
main () 
{
	stack * sol ;
	sol = create_stack(8, sizeof(int)) ;

	int curr = 0 ;
	while (get_size(sol) < 8) {
		while (curr < 64) {
			if (!conflict(sol, curr)) {
				push(sol, &curr) ;
				curr = 0 ;
				break ;
			}
			curr += 1 ;
		}
		if (curr == 64) {
			pop(sol, &curr) ; 
			curr += 1 ;
		}
	}

	while (!is_empty(sol)) {
		int elem ;
		pop(sol, &elem) ;
		printf("(%d,%d)\n", X(elem), Y(elem)) ;
	}
	return 0 ;
}
