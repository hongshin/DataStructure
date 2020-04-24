#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

typedef struct term {
	int coef ;
	int expo ;
} term_t ;


typedef linkedlist_t polynomial ;

void
polynomial_add_term(polynomial * p, term_t * n)
{
	node_t * curr = p->right ;
	while (curr != p) {
		term_t * t = (term_t *) curr->element ;
		if (n->expo > t->expo) {
			break ;
		}
		else if (n->expo == t->expo) {
			t->coef += n->coef ;
			return ;
		}
		curr = curr->right ;
	}
	linkedlist_insert(curr->left, n, sizeof(term_t)) ;
}

void
polynomial_print(polynomial * p)
{
	node_t * curr ;

	curr = p->right ;
	while (curr != p) {	
		term_t * t ;
		t = (term_t *) curr->element ;
		printf("(%d) x^%d", t->coef, t->expo) ;
		
		curr = curr->right ;
		if (curr != p)
			printf(" + ") ;
		else 
			printf("\n") ;
	}
}

polynomial *
polynomial_add (polynomial * p1, polynomial * p2)
{
	polynomial * r = linkedlist_alloc(sizeof(term_t)) ;

	term_t t1, t2 ;
	int i1 = 0 , i2 = 0 ;

	while (i1 < linkedlist_length(p1) && i2 < linkedlist_length(p2)) {
		linkedlist_get(p1, i1, &t1) ;
		linkedlist_get(p2, i2, &t2) ;

		if (t1.expo > t2.expo) {
			polynomial_add_term(r, &t1) ;
			i1 += 1 ;
		}
		else if (t2.expo > t1.expo) {
			polynomial_add_term(r, &t2) ;
			i2 += 1 ;
		}
		else /* t1->expo == t2->expo */ {
			term_t t ;
			t.coef = t1.coef + t2.coef ;
			t.expo = t1.expo ;
			polynomial_add_term(r, &t) ;
			i1 += 1 ;
			i2 += 1 ;
		}
	}
	while (i1 < linkedlist_length(p1)) {
		linkedlist_get(p1, i1, &t1) ;
		polynomial_add_term(r, &t1) ;
		i1 += 1 ;
	}
	while (i2 < linkedlist_length(p2)) {
		linkedlist_get(p2, i2, &t2) ;
		polynomial_add_term(r, &t2) ;
		i2 += 1 ;
	}
	return r ;
}

polynomial * 
polynomial_mult (polynomial * p1, polynomial * p2)
{
	node_t * n1, * n2 ;
	term_t * t1, * t2 ;
	polynomial * pr = linkedlist_alloc(sizeof(term_t)) ;

	for (n1 = p1->right ; n1 != p1 ; n1 = n1->right) {
		t1 = n1->element ;
		for (n2 = p2->right ; n2 != p2 ; n2 = n2->right) {
			t2 = n2->element ;

			term_t tr ;
			tr.coef = t1->coef * t2->coef ;
			tr.expo = t1->expo + t2->expo ;
			polynomial_add_term(pr, &tr) ;
		}
	}
	return pr ;
}

int 
main () 
{
	polynomial * p1 ;
	polynomial * p2 ; 
	polynomial * pr ;

	p1 = linkedlist_alloc(sizeof(term_t)) ;
	p2 = linkedlist_alloc(sizeof(term_t)) ;

	term_t t ;
	t.coef = 1 ; t.expo = 0 ;	polynomial_add_term(p1, &t) ; 
	t.coef = 3 ; t.expo = 14 ; 	polynomial_add_term(p1, &t) ;
	t.coef = 2 ; t.expo = 8 ;	polynomial_add_term(p1, &t) ;

	t.coef = 8 ; t.expo = 14 ; 	polynomial_add_term(p2, &t) ;
	t.coef = -3 ; t.expo = 10 ;	polynomial_add_term(p2, &t) ;
	t.coef = 10 ; t.expo = 6 ;	polynomial_add_term(p2, &t) ;

	//pr = polynomial_add(p1, p2) ;
	pr = polynomial_mult(p1, p2) ;

	polynomial_print(p1) ;
	polynomial_print(p2) ;
	polynomial_print(pr) ;

	linkedlist_free(p1) ;
	linkedlist_free(p2) ;
	linkedlist_free(pr) ;
}
