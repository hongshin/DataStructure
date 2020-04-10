#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

typedef enum { Value, Operator } token_type ;

typedef struct {
	int value ; 
	char operator ; 
	token_type type ;
} token_t ;

void
print_stack (stack * st)
{
	int i ;
	token_t t ;
	
	printf("> " ) ;
	for (i = 0 ; i < get_size(st); i++) {
		get_element(st, i, &t) ;
		if (t.type == Value)
			printf("[%d] ", t.value) ;
		else /* t.type == Operator */
			printf("[%c] ", t.operator) ;
	}
	printf("\n") ;
}

int
main () 
{
	int i ; 
	stack * st ;

	st = create_stack(100, sizeof(token_t)) ;
	
	char buf[16] = { 0x0 } ;

	while (!(buf[0] == ';' && get_size(st) == 1)) {
		print_stack(st) ;

		if (get_size(st) >= 3) {
			token_t oprt, val1, val2 ;

			pop(st, &val2) ;
			pop(st, &val1) ;
			pop(st, &oprt) ;

			if (val1.type == Value && val2.type == Value && oprt.type == Operator) {
				token_t res ;

				res.type = Value ;
				switch (oprt.operator) {
					case '+':
						res.value = val1.value + val2.value ;
						break ;
					case '-':
						res.value = val1.value - val2.value ;
						break ;
					case '*':
						res.value = val1.value * val2.value ;
						break ;
					case '/':
						res.value = val1.value / val2.value ;
						break ;
				}
				push(st, &res) ;
				continue ;
			}
			else {
				push(st, &oprt) ;
				push(st, &val1) ;
				push(st, &val2) ;
			}
		}
		
		scanf("%s", buf) ;
		printf("> read %s\n", buf) ;

		if (buf[0] == ';') {
			continue ;
		}
		else if (isdigit(buf[0])) {
			token_t tok ;
			tok.type = Value ;
			tok.value = atoi(buf) ;
			push(st, &tok) ;
		}
		else /* operator */ {
			token_t tok ;
			tok.type = Operator ;
			tok.operator = buf[0] ;
			push(st, &tok) ;
		}
	}

	token_t result ;
	pop(st, &result) ;
	printf("%d\n", result.value) ;

	delete_stack(st) ;
}
