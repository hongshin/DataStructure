#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "stack.h"

int
main () 
{
	int n_tokens ;
	int i ; 
	stack * st ;

	st = create_stack(100, sizeof(int)) ;

	scanf("%d", &n_tokens) ;

	char buf[64] ;

	for (i = 0 ; i < n_tokens ; i++) {
		scanf("%s", buf) ;
		if (isdigit(buf[0])) {
			int val = atoi(buf) ;
			push(st, &val) ;
		}
		else {
			int val1, val2, ret ;
			switch (buf[0]) {
				case '+': 
					pop(st, &val2) ;
					pop(st, &val1) ;
					ret = val1 + val2 ;
					push(st, &ret) ;
					break ;
				case '-': 
					pop(st, &val2) ;
					pop(st, &val1) ;
					ret = val1 - val2 ;
					push(st, &ret) ;
					break ;
				case '*': 
					pop(st, &val2) ;
					pop(st, &val1) ;
					ret = val1 * val2 ;
					push(st, &ret) ;
					break ;
				case '/': 
					pop(st, &val2) ;
					pop(st, &val1) ;
					ret = val1 / val2 ;
					push(st, &ret) ;
					break ;
			}
		}
	}

	int result ;
	pop(st, &result) ;
	printf("%d\n", result) ;

	delete_stack(st) ;
}
