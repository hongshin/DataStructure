#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

typedef struct {
	int x ;
	int y ;
	int m ;
} pos ;

int d[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}} ;

int visited[8][8] ;

pos init ;
pos dest ;

void
print_element (void * p)
{
	pos * elem = (pos *) p ;
	printf("%d,%d,%d", elem->x, elem->y, elem->m) ;
}

int
main () 
{
	queue * tasks ;
	tasks = create_queue(64, sizeof(pos)) ;

	scanf("%d %d", &(init.x), &(init.y)) ;
	scanf("%d %d", &(dest.x), &(dest.y)) ;

	init.m = 0 ;
	enqueue(tasks, &init) ;
	while (!is_empty(tasks)) {
		pos curr ;
		dequeue(tasks, &curr) ;

		if (curr.x == dest.x && curr.y == dest.y) {
			printf("%d\n", curr.m) ;
			return 0 ;
		}

		if (visited[curr.y][curr.x])
			continue ;

		visited[curr.y][curr.x] = 1 ;

		int i ;
		for (i = 0 ; i < 8 ; i++) {
			pos next ;
			next.x = curr.x + d[i][0] ;
			next.y = curr.y + d[i][1] ;
			next.m = curr.m + 1 ;

			if (0 <= next.x && next.x < 8 && 0 <= next.y && next.y < 8) {
				enqueue(tasks, &next) ;
			}
		}
	}

	printf("unreachable\n") ;

	delete_queue(tasks) ;
	return 0 ;
}
