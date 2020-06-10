#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstree.h"

bst_t * 
bst_create (size_t usize, int (* cmp)(void *e1, void *e2)) 
{
	bst_t * t = (bst_t *) malloc(sizeof(bst_t)) ;
	t->root = 0x0 ;
	t->usize = usize ;
	t->cmp = cmp ;
	return t ;
}

bst_node_t *
_bst_search (bst_t * t, void * data)
{
	bst_node_t * prev, * curr ;
	prev = 0x0 ;
	for (curr = t->root ; curr != 0x0 && t->cmp(curr->data, data) != 0 ; ) {
		prev = curr ;
		if (t->cmp(data, curr->data) < 0) {
			curr = curr->left ;
		}
		else {
			curr = curr->right ;
		}
	} 
	if (curr != 0x0)
		return curr ;
	return prev ;
}

int
bst_insert (bst_t * t, void * data) 
{
	bst_node_t * n = (bst_node_t *) malloc(sizeof(bst_node_t)) ;
	n->data = (char *) malloc(t->usize) ;
	memcpy(n->data, data, t->usize) ;
	n->left = 0x0 ;
	n->right = 0x0 ;

	bst_node_t * target ;
	target = _bst_search(t, data) ;

	if (target != 0x0 && t->cmp(target->data, data) == 0)
		return 1 ;
	
	if (target == 0x0) {
		t->root = n ;
		n->parent = 0x0 ;
	}
	else {
		n->parent = target ;
		if (t->cmp(data, target->data) < 0) {
			target->left = n ;
		}
		else {
			target->right = n ;
		}
	}

	return 0 ;
}

void *
bst_search (bst_t * t, void * data)
{
	bst_node_t * n ; 
	n = _bst_search(t, data) ;
	if (n == 0x0)
		return 0x0 ;
	if (t->cmp(n->data, data) != 0)
		return 0x0 ;
	return n->data ;
}

int
bst_remove (bst_t * t, void * data)
{
	bst_node_t * n ;
	n = _bst_search(t, data) ;
	if (n == 0x0 || t->cmp(n->data, data) != 0) 
		return 1 ;

	bst_node_t ** in_ptr ;
	if (n->parent == 0x0) {
		in_ptr = &(t->root) ;
	}
	else if (n->parent->left == n) {
		in_ptr = &(n->parent->left) ;
	}
	else {
		in_ptr = &(n->parent->right) ;
	}

	if (n->left == 0x0 && n->right == 0x0) {
		*in_ptr = 0x0 ;
		free(n->data) ;
		free(n) ;
	}
	else if (n->left != 0x0 && n->right == 0x0) {
		*in_ptr = n->left ;
		n->left->parent = n->parent ;
		free(n->data) ;
		free(n) ;
	}
	else if (n->left == 0x0 && n->right != 0x0) {
		*in_ptr = n->right ;
		n->right->parent = n->parent ;
		free(n->data) ;
		free(n) ;
	}
	else {
		bst_node_t * n_max ;
		for (n_max = n->left ; n_max->right != 0x0 ; ) {
			n_max = n_max->right ;
		}

		free(n->data) ;
		n->data = n_max->data ;
		if (n_max->left != 0x0) {
			n_max->left->parent = n->parent ;
			n_max->parent->right = n_max->left ;			
		}
		else {
			n_max->parent->right = 0x0 ;
		}
		free(n_max) ;
	}
	return 0 ;
}

void
bst_node_print (bst_node_t * n, void (* print)(void * data))
{
	printf("(") ;
	if (n->left != 0x0) 
		bst_node_print(n->left, print) ;
	else
		printf("-") ;
	printf(",") ;
	print(n->data) ;
	printf(",") ;
	if (n->right != 0x0) 
		bst_node_print(n->right, print) ;
	else
		printf("-") ;
	printf(")") ;
}

void
bst_print (bst_t * t, void (* print)(void * data)) 
{
	if (t->root != 0x0)
		bst_node_print(t->root, print) ;
	printf("\n") ;
}

void
bst_node_free (bst_node_t * n)
{
	if (n->left != 0x0)
		bst_node_free(n->left) ;
	if (n->right != 0x0)
		bst_node_free(n->right) ;
	free(n->data) ;
}

void
bst_free (bst_t * t)
{
	if (t->root != 0x0) 
		bst_node_free(t->root) ;
	free(t) ;
}
