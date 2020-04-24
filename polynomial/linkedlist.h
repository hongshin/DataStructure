struct node {
	void * element ;
	struct node * left ; 
	struct node * right ;
} ;

typedef struct node node_t ;
typedef struct node linkedlist_t ;

linkedlist_t * 
linkedlist_alloc (int unit)  ;

void
linkedlist_free (linkedlist_t * l) ;

int 
linkedlist_length (linkedlist_t * l) ;

void
linkedlist_insert (node_t * left, void *, int unit) ;

void
linkedlist_insert_first (linkedlist_t * l, void * e) ;

void
linkedlist_insert_last (linkedlist_t * l, void * e) ;

int
linkedlist_remove (linkedlist_t * l, node_t * n) ;

int
linkedlist_remove_first (linkedlist_t * l, void * e) ;

int
linkedlist_remove_last (linkedlist_t * l, void * e) ;

int
linkedlist_get (linkedlist_t * l, int pos, void * e) ;
