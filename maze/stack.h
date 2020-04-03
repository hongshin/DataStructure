typedef 
	struct {
		char * buffer ;
		int unit ;
		int capacity ;
		int top ;
	} 
	stack ;

stack * 
create_stack (int capacity, int unit) ;

void
delete_stack (stack * stack) ;

int 
push (stack * stack, void * elem) ;

int
pop (stack * stack, void * elem) ;

int 
is_empty (stack * stack) ;

int 
is_full (stack * stack) ;

int
get_size (stack * stack) ;

int
get_element (stack * stack, int index, void * elem) ;
