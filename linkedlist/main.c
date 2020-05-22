#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedlist.h"

void
free_string (void * p)
{ 
	char ** s = (char **) p ;
	free(*s) ;
}

int
cmp_string (void * e1, void * e2)
{
	char * s1 = *((char **) e1) ;
	char * s2 = *((char **) e2) ;

	while (*s1 != 0x0 && *s2 != 0x0 && *s1 == *s2) {
		s1++ ;
		s2++ ;
	}
	if (*s1 == 0x0 && *s2 != 0x0)
		return -1 ;
	
	if (*s1 != 0x0 && *s2 == 0x0)
		return 1 ;

	return (*s1 - *s2) ;
}

void
print_string (void * p) 
{
	char * s = *((char **) p) ;
	printf("%s\n", s) ;
}

int 
main () 
{
	linkedlist_t * l ; 
	l = linkedlist_alloc(sizeof(char *)) ;

	FILE * fp = fopen("wordset.txt", "r") ;
	if (fp == 0x0) {
		perror("failed to open wordset.txt") ;
		exit(1) ;
	}

	while (!feof(fp)) {
		char s[256] ;

		int i = 0 ;
		int c ;
		while ((c = fgetc(fp)) != '\n' && c != EOF) {
			s[i] = c ;
			i++ ;
		}
		if (i != 0) {
			s[i] = 0x0 ;
			char * str = strdup(s) ;
			linkedlist_insert_last(l, &str) ;
		}
	}
	fclose(fp) ;

	linkedlist_sort(l, cmp_string) ;

	int n ; 
	char * s ;
	scanf("%d", &n) ;
	linkedlist_get(l, n, &s) ;
	printf("%s\n", s) ;

	//linkedlist_print(l, print_string) ;
	linkedlist_free(l, 0x0 /*free_string*/) ;
}
