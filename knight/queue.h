typedef 
	struct {
		void * buffer ;
		int unit ;
		int capacity ;
		int front ;
		int rear ;
		int full ;
	} 
	queue ;

queue * 
create_queue (int capacity, int unit) ;

void
delete_queue (queue * que) ;

int 
enqueue (queue * que, void * elem) ;

int
dequeue (queue * que, void * elem) ;

int 
is_empty (queue * que) ;

int 
is_full (queue * que) ;

void
print_queue (queue * que, void (* print_element)(void * element)) ;

