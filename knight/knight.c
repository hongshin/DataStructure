#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

const int d[8][2] = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, 
					{1, -2}, {1, 2}, {2, -1}, {2, 1}} ;

typedef struct {
	int x ;
	int y ;
} pos ; 

typedef struct {
	pos p ;
	int m ;
} task ;

int visited[8][8] ;
pos ancestor[8][8] ;

pos init ;
pos dest ;

void
print_element (void * p)
{
	task * elem = (task *) p ;
	printf("%d,%d,%d", elem->p.x, elem->p.y, elem->m) ;
}

int
main () 
{
	queue * tasks ;

	tasks = create_queue(64, sizeof(task)) ;

	scanf("%d %d", &(init.y), &(init.x)) ;
	scanf("%d %d", &(dest.y), &(dest.x)) ;


	visited[init.y][init.x] = 1 ;
	ancestor[init.y][init.x] = init ;

	task init_task ;
	init_task.p = init ;
	init_task.m = 0 ;
	enqueue(tasks, &init_task) ;	
	while (!is_empty(tasks)) {
		task curr ;

		dequeue(tasks, &curr) ;
		if (curr.p.x == dest.x && curr.p.y == dest.y) {
			printf("%d\n", curr.m) ;

			printf("(%d,%d)", curr.p.y, curr.p.x) ;
			pos a = curr.p ;
			while (a.x != ancestor[a.y][a.x].y || a.y != ancestor[a.y][a.x].x) {
				a = ancestor[a.y][a.x] ;
				printf("-(%d,%d)", a.y, a.x) ;
			}
			printf("\n") ;
			delete_queue(tasks) ;
			exit(0) ;
		}
		else {
			int i_d ;
			for (i_d = 0 ; i_d < 8 ; i_d++) {
				task next ;

				next.p.y = curr.p.y + d[i_d][0] ;
				next.p.x = curr.p.x + d[i_d][1] ;
				next.m = curr.m + 1 ;
				if (0 <= next.p.x && next.p.x < 8) {
					if (0 <= next.p.y && next.p.y < 8) {
						if (visited[next.p.y][next.p.x] == 0) {
							enqueue(tasks, &next) ; 
							visited[next.p.y][next.p.x] = 1 ;
							ancestor[next.p.y][next.p.x] = curr.p ;
						}
					}
				}
			}
		}
	}
	// assume is_empty() 
	printf("unreachable\n") ;
	delete_queue(tasks) ;
	return 0 ;
}
