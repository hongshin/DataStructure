#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"

void
print_stack (stack * st)
{
	int i ;
	for (i = 0 ; i < get_size(st) ; i++) {
		int num ;
		get_element(st, i, &num) ;
		printf("[%d]", num) ;
	}
	printf(".\n") ;
}


int
main ()
{
	stack * st ;
	st = create_stack(100, sizeof(int)) ;

	char tok[8] ;
	do {
		print_stack(st) ;

		scanf("%s", tok) ;

		if (tok[0] == ';') 
			break ;

		if (isdigit(tok[0])) {
			int num = atoi(tok) ;
			push(st, &num) ;
		}
		else /* operator */ {
			switch (tok[0]) {
				case '+' : {
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					res = n1 + n2 ;
					push(st, &res) ;
					break ;
				} 

				case '-' : {
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					res = n1 - n2 ;
					push(st, &res) ;
					break ;
				}

				case '*' : {
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					res = n1 * n2 ;
					push(st, &res) ;
					break ;
				}

				case '/' : {
					int n1, n2, res ;
					pop(st, &n2) ;
					pop(st, &n1) ;
					res = n1 / n2 ;
					push(st, &res) ;
					break ;
				}
			}
		}
	} while (tok[0] != ';') ;

	int result ;
	pop(st, &result) ;
	printf("%d\n", result) ;
	
	delete_stack(st) ;
	return 0 ;
}
