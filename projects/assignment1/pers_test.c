#include "mymalloc.h"


int main(){

	//initialize the heap on startup
	init_heap();		
	
	int* ptr = (int*)malloc(20);
	int* ptr2 = (int*)malloc(20);
	int* ptr3 = (int*) malloc(1000);
	
	print_heap_status();
	printf("********************\n");
	free(ptr3);
	free(ptr);	
	free(ptr2);
	print_heap_status();	
	
	return 0;
}
