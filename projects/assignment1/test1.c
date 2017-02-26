#include "mymalloc.h"

int main(){
	
	//initialize the heap on startup
	init_heap();		
	
	int* ptr = (int*)malloc(20);
	int* ptr2 = (int*)malloc(20);
	
	print_heap_status();
	printf("********************\n");
	free(ptr);	
	free(ptr);
	print_heap_status();	
	return 0;
}
