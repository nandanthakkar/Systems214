/*
 * Authors: Douglas Rudolph, Brandon Yu
 * File: memgrind.c
 * Course: Systems Programming
 */
#include <stdlib.h>
#include "mymalloc.h"
#include <time.h>

int main(){

	//TEST CASE A
	//create char array to store all the different malloced nodes
	char* arr[1000];
	//create clock to run test
	clock_t one;
	//start clock
	one = clock();

	//run test
	int i;
	for(i=0; i<1000; i++){
		arr[i] = malloc(1);		
	}

	for(i=0; i<1000; i++){
		free(arr[i]);
	}
	//get total time
	one = clock() - one;
	//convert to double
	double time_taken = ((double)one)/CLOCKS_PER_SEC;
	
	//print resulting time
	printf("Test Case A: %f\n", time_taken);

	//TEST CASE B
	//create var to store average and reset time taken
	double avg=0;
	time_taken=0;
	//create a clock for test 2 
	clock_t two;	

	// run test
	for(i=0; i<1000; i++){
		two = clock();
		time_taken=0;
		init_heap();
		char* ptr = malloc(1);
		free(ptr);
		two = clock() - two;
		time_taken = ((double)two)/CLOCKS_PER_SEC;
		avg+=time_taken;
	}

	//print out the average runtime for test 2
	printf("Test Case B: %f\n", avg/1000);
	
	//TEST CASE C
	//reset the avg var and time_take from previous test
	avg=0;
	time_taken=0;
	//create clock for test 3
	clock_t three;
	int* ptr;
	//run test
	for(i=0;i<100; i++){
		time_taken=0;
		init_heap();
		three = clock();
		srand(time(NULL));
		int r = rand();
		
		if(r%2==0){
			ptr = (int*)malloc(1);	
		}
		else if(r%3==0){
			free(ptr);
		}	
	
		three = clock()-three;
		time_taken = ((double)three)/CLOCKS_PER_SEC;
		avg+=time_taken;
	}
	//print the avg time
	printf("Test Case C: %f\n", avg/100);
	
	//TEST CASE D
	//create a clock for test 4 and reset timinig variables
	clock_t four;
	time_taken=0;
	avg=0;
	//rn the random test for test 4
	for(i=0; i<100; i++){
		time_taken=0;
		four = clock();
		init_heap();
		int r = rand();
		if(r%3==0){
			ptr = (int*)malloc(1);	
		}
		else if(r%2==0){
			free(ptr);
		}
		four = clock()-four;
		time_taken = ((double)four)/CLOCKS_PER_SEC;
		avg+=time_taken;
	}
	//print the result
	printf("Test Case D: %f\n", avg/100);

	
	//TEST CASE E
	//create a clock, reset timing variables
	clock_t five;
	time_taken=0;
	avg=0;

	//run test
	for(i=0; i<100; i++){
		time_taken=0;
		five = clock();
		init_heap();		
	
		int* ptr = (int*)malloc(20);
		int* ptr2 = (int*)malloc(20);
		int* ptr3 = (int*) malloc(1000);
		free(ptr3);
		free(ptr);	
		free(ptr2);	

		five = clock() - five;
		time_taken = ((double)five)/CLOCKS_PER_SEC;
		avg+=five;
	}
	//print out the avg
	printf("Test Case E: %f\n", avg/100);



	//TEST CASE F
	//reset timing variables and create a clock for test 6
	clock_t six;
	time_taken=0;
	avg=0;

	//run test
	for(i=0; i<100; i++){
		time_taken=0;
		six = clock();		
		init_heap();
		int* ptr = (int*)malloc(20);
		int* ptr2 = (int*)malloc(20);
		
		free(ptr2);
		free(ptr);
		six = clock() - six;
		time_taken = ((double)five)/CLOCKS_PER_SEC;
		avg+=time_taken;
	}	
	//print avg
	printf("Test Case F: %f\n", avg/100);
}
