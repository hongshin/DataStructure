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

	char buf[16] ;
	do {
		print_stack(st) ;

		scanf("%s", buf) ; printf("> read %s.\n", buf) ;

		if (buf[0] == ')') {
			token_t val1, oprt, val2, res ;

			pop(st, &val2) ;
			pop(st, &oprt) ;
			pop(st, &val1) ;

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
		}
		else {
				if (buf[0] == '(') {
						// skip
				}
				else if (isdigit(buf[0])) {
						token_t tok ;
						tok.value = atoi(buf) ;
						tok.type = Value ;
						push(st, &tok) ;
				}
				else if (buf[0] == '+' || buf[0] == '-' || buf[0] == '*' || buf[0] == '/') {
						token_t tok ;
						tok.operator = buf[0] ;
						tok.type = Operator ;
						push(st, &tok) ;
				}
				else {
						// semicolon or , it must not be reached.
				}
		}
	} while (buf[0] != ';') ;

	token_t result ;
	pop(st, &result) ;
	printf("%d\n", result.value) ;

	delete_stack(st) ;
}
