#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include "stack.h"

typedef enum { 
	UP, DOWN, LEFT, RIGHT, DONE 
} dir ;

enum cell {
	EMPTY, WALL, PATH
} ;

typedef struct {
	int x ;
	int y ;
	dir d ;
} decision ;

int X, Y ;
int m[20][20] ;

void
print_map ()
{
	int i, j ;

	for (i = 0 ; i < X + 2 ; i++)
		printf("XX") ;
	printf("\n") ;
	for (i = 0 ; i < Y ; i++) {
		printf("XX") ;
		for (j = 0 ; j < X ; j++) {
			if (m[i][j] == WALL) 
				printf("XX") ;
			else if (m[i][j] == PATH) 
				printf("::") ;
			else 
				printf("  ") ;
		}
		printf("XX\n") ;
	}
	for (i = 0 ; i < X + 2 ; i++)
		printf("XX") ;
	printf("\n") ;
}


int
main ()
{
	int i, j ;

	FILE * fp = fopen("maze2.txt", "r") ;
	fscanf(fp, "%d %d", &X, &Y) ;
	for (i = 0 ; i < Y ; i++) {
		for (j = 0 ; j < X ; j++) {
			fscanf(fp, "%d", &(m[i][j])) ;
		}
	}
	fclose(fp) ;


	stack * path = create_stack(400, sizeof(decision)) ;
	
	decision curr, next ;

	curr.x = 0 ;
	curr.y = 0 ;
	curr.d = UP ; // UP=0

	push(path, &curr) ;
	while (!is_empty(path)) {
		pop(path, &curr) ; 

		if (curr.x == X-1 && curr.y == Y-1) {
			int i ;
			decision c ;
			for (i = 0 ; i < get_size(path) ; i++) {
				get_element(path, i, &c) ;
				m[c.y][c.x] = PATH ;
			}
			print_map() ;
			return 0 ;
		}
		
		if (curr.d == UP) {
			next.x = curr.x ;
			next.y = curr.y - 1 ;
			next.d = UP ;
		}
		else if (curr.d == DOWN) {
			next.x = curr.x ;
			next.y = curr.y + 1 ;
			next.d = UP ;
		}
		else if (curr.d == LEFT) {
			next.x = curr.x - 1 ;
			next.y = curr.y ;
			next.d = UP ;
		}
		else if (curr.d == RIGHT) {
			next.x = curr.x + 1 ;
			next.y = curr.y ;
			next.d = UP ;
		}
		else { } // curr.d == DONE 

		if (curr.d != DONE) {
			curr.d += 1 ;
			push(path, &curr) ;
		}
		else {
			continue ;
		}
	
		if (0 <= next.x && next.x < X) {
			if (0 <= next.y && next.y < Y) {
				if (m[next.y][next.x] == EMPTY) {
					for (i = 0 ; i < get_size(path) ; i++) {
						decision e ;
						get_element(path, i, &e) ;
						if (e.x == next.x && e.y == next.y)
							break ;
					}
					if (i == get_size(path)) 
						push(path, &next) ;
				}
			}
		}
	}

	return 0 ;
}
