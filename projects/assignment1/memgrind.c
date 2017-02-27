#include "mymalloc.h"
#include <time.h>

int main(){

	//TEST CASE A
	//init_heap();
	char* arr[1000];
	int i;
	//calculate time
	//struct timeval start, end, result;
	//gettimeofday(&start, NULL);

	for(i=0; i<1000; i++){
		arr[i] = malloc(1);		
	}

	for(i=0; i<1000; i++){
		free(arr[i]);
	}
	
	//gettimeofday(&end, NULL);
	//timersub(&start, &end, &result);
	//long int total = result.tv_usec;
	//printf("Test Case 1: %li", total);

	//TEST CASE B	
	for(i=0; i<1000; i++){
		init_heap();
		char* ptr = malloc(1);
		free(ptr);
	}
	
	//TEST CASE C
	for(i=0;i<100; i++){}
	
	//TEST CASE D
	for(i=0; i<100; i++){}
	
	//TEST CASE E
	for(i=0; i<100; i++){
		init_heap();		
	
		int* ptr = (int*)malloc(20);
		int* ptr2 = (int*)malloc(20);
		int* ptr3 = (int*) malloc(1000);
	
		free(ptr3);
		free(ptr);	
		free(ptr2);	
	}

	//TEST CASE F
	for(i=0; i<100; i++){
		init_heap();
		int* ptr = (int*)malloc(20);
		int* ptr2 = (int*)malloc(20);
		
		free(ptr2);
		free(ptr);
	}	
}
