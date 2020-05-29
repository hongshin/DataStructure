#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

char s[256] = "1(2(3(4,5),6),7(8),9(10(11),12,13))" ;

tree_t *
read_a_tree(char *s)
{
	char * begin, * end, * sub ;
	int n ;
	int data ;	

	data = atoi(s) ;
	node_t * t = tree_create_node(data) ;

	for (begin = s + 1 ; *begin != '(' && *begin != ')' && *begin != ',' ; begin++) ;
	if (*begin == ')' || *begin == ',') 
		return t ;

	// *begin == '('
	sub = begin + 1 ;
	for (end = begin + 1, n = 0 ; n > 0 || *end != ')' ; end++) {
		if (*end == '(') {
			n++ ;
		}
		if (*end == ')') {
			n-- ;
		}
		if (n == 0 && *end == ',') {
			tree_add_child(t, read_a_tree(sub)) ;
			sub = end + 1 ;
		}
	}
	tree_add_child(t, read_a_tree(sub)) ;

	return t ;
}

int
main ()
{
	char s[256] = "1(2(3(4,5),6),7(8),9(10(11),12,13))" ;
	char newline ;
	//scanf("%255[^\n]", s, &newline) ;

	tree_t * t ;
	t = read_a_tree(s) ;
	tree_print(t) ;

	printf("height: %d\n", tree_height(t)) ;

	tree_print(tree_search(t, 3)) ;

	return 0 ;
}
