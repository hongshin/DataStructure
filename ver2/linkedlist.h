struct node {
	int element ;
	struct node * next ; 
} ;

struct linkedlist {
	int length ;
	struct node * first ;
	struct node * last ;
} ;

typedef struct node node_t ;
typedef struct linkedlist linkedlist_t ;

linkedlist_t * 
linkedlist_alloc()  ;

void
linkedlist_push (linkedlist_t * l, int e) ;

void
linkedlist_insert (linkedlist_t * l, int e) ;

int
linkedlist_retrieve (linkedlist_t * l, int pos, int * e) ;

int 
linkedlist_length (linkedlist_t * l) ;

int 
linkedlist_pop (linkedlist_t * l, int * e) ;

int
linkedlist_remove (linkedlist_t * l, int e) ;
