typedef struct node node_t ;

typedef struct node * linkedlist_t ;

struct node {
	int element ;
	linkedlist_t tail ; 
} ;

linkedlist_t  
linkedlist_alloc()  ;

void
linkedlist_push (linkedlist_t * l, int e) ;

int
linkedlist_retrieve (linkedlist_t l, int pos, int * e) ;

int 
linkedlist_length (linkedlist_t l) ;

int 
linkedlist_pop (linkedlist_t * l, int * e) ;

int
linkedlist_remove (linkedlist_t * l, int e) ;
