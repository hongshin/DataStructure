struct arraylist {
	int capacity ;
	int length ;
	int * elements ;
} ;

typedef struct arraylist arraylist_t ;

arraylist_t * 
arraylist_alloc ()  ;

void
arraylist_insert (arraylist_t * l, int e) ;

int
arraylist_retrieve (arraylist_t * l, int pos, int * e) ;

int 
arraylist_length (arraylist_t * l) ;

int 
arraylist_pop (arraylist_t * l, int * e) ;
