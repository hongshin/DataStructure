struct sortedlist {
	int capacity ;
	int length ;
	int * elements ;
} ;

typedef struct sortedlist sortedlist_t ;

sortedlist_t * 
sortedlist_alloc ()  ;

void
sortedlist_insert (sortedlist_t * l, int e) ;

int
sortedlist_retrieve (sortedlist_t * l, int pos, int * e) ;

int 
sortedlist_length (sortedlist_t * l) ;

int 
sortedlist_pop (sortedlist_t * l, int * e) ;

int
sortedlist_lookup (sortedlist_t * l, int v) ;

sortedlist_t *
sortedlist_merge (sortedlist_t * l1, sortedlist_t * l2) ;
