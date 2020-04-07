#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

typedef enum { Value, Operator } token_type ;

typedef struct {
	int value ;
	char operator ;
	token_type type ;
} token_t ;

int n_tokens ;
token_t tokens[100] ;

void
print_stack (stack * st)
{
	int i ;
	token_t t ;
	for (i = 0 ; i < get_size(st); i++) {
		get_element(st, i, &t) ;
		printf("(%d,%c) ", t.value, t.operator) ;
	}
	printf("\n") ;
}


int
main () 
{
	int i ; 
	stack * st ;

	st = create_stack(100, sizeof(token_t)) ;
	
	char buf[64] ;
	i = 0 ;
	do {
		scanf("%s", buf) ;

		switch (buf[0]) {
			case ';':
				break ;

			case '+':
			case '-':
			case '*':
			case '/':
				tokens[i].operator = buf[0] ;
				tokens[i].type = Operator ;
				i++ ;
				break ;

			default:
				tokens[i].value = atoi(buf) ;
				tokens[i].type = Value ;
				i++ ;
				break ;
		}
	}
	while (buf[0] != ';') ;
	n_tokens = i ;

	i = 0 ; 
	while (i < n_tokens || get_size(st) > 1) {
		token_t tok1, tok2, tok_op ;
		print_stack(st) ;	
		if (pop(st, &tok1) == 0) {
			if (pop(st, &tok2) == 0) {
				if (tok1.type == Value && tok2.type == Value) {
					pop(st, &tok_op) ;
					token_t res ;
					res.type = Value ;
					switch (tok_op.operator) {
						case '+':
							res.value = tok2.value + tok1.value ;
							break ;
						case '-':
							res.value = tok2.value - tok1.value ;
							break ;
						case '*':
							res.value = tok2.value * tok1.value ;
							break ;
						case '/':
							res.value = tok2.value / tok1.value ;
							break ;
					}
					push(st, &res) ;
					continue ;
				}
				else {
					push(st, &tok2) ;
					push(st, &tok1) ;
				}
			}
			else {
				push(st, &tok1) ;
			}
		}
		if (i < n_tokens) 
			push(st, &(tokens[i])) ;
		i++ ;
	}

	token_t result ;
	pop(st, &result) ;
	printf("%d\n", result.value) ;

	delete_stack(st) ;
}
