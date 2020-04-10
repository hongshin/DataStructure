#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

typedef enum { Value, Operator, Open } token_type ;

typedef struct {
	int value ;
	char operator ;
	token_type type ;
} token_t ;

void
print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		token_t tok ;
		get_element(st, i, &tok) ;
		if (tok.type == Value) 
			printf("[%d] ", tok.value) ;
		else if (tok.type == Operator)
			printf("[%c] ", tok.operator) ;
		else 
			printf("[(] ") ;
	}
	printf(".\n") ;
}


int 
prec (char oprt) 
{
	if (oprt == '+') {
		return 1 ;		
	}
	else if (oprt == '-') {
		return 1 ;
	}
	else if (oprt == '*') {
		return 2 ;
	}	
	else if (oprt == '/') {
		return 2 ;
	}

	return 0 ; 
}

int
main () 
{
	int i ; 
	token_t tok ;
	stack * st ;

	st = create_stack(100, sizeof(token_t)) ;
	
	tok.type = Open ;
	push(st, &tok) ;

	char s[16] = { 0x0 } ;
	do {
		print_stack(st) ; 
		scanf("%s", s) ;	printf("> read: %s.\n", s) ;

		if (s[0] == '(') {
			token_t tok ;
			tok.type = Open ;
			push(st, &tok) ;
		}
		else if (isdigit(s[0])) {  						// 1 * 2 + 3 
			token_t tok ;
			tok.type = Value ;
			tok.value = atoi(s) ;
			push(st, &tok) ;
		}
		else if (s[0] == ')' || s[0] == ';') {
			token_t val1, oprt, val2, res, top ;

			do {
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
				pop(st, &top) ;
				if (top.type != Open)
					push(st, &top) ;
				push(st, &res) ;
			} while (top.type != Open) ;
		}
		else if (s[0] == '+' || s[0] == '-' || s[0] == '*' || s[0] == '/') {
			token_t tok ;						 
			tok.operator = s[0] ;				          
			tok.type = Operator ;

			while (get_size(st) >= 3) {	
				token_t val1, val2, oprt, res ;
				
				pop(st, &val2) ;
				pop(st, &oprt) ;
				pop(st, &val1) ;

				if (!(prec(oprt.operator) < prec(tok.operator))) {
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
					push(st, &val1) ;
					push(st, &oprt) ;
					push(st, &val2) ;
					break ; 
				}
			}
			push(st, &tok) ;
		}
		else {
			// must not be reached.
		}
	} while (s[0] != ';') ;

	token_t result ;
	pop(st, &result) ;
	printf("%d\n", result.value) ;

	delete_stack(st) ;
}
