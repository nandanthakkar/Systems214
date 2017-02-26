#include "mymalloc.h"

//comment to push

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

/*
 * 1. Takes in the amount of memory a user wants to allocate
 * 2. Checks to see if there is enough room in the Heap
 *    - if yes: Then add a new MemNode to the heap
 *      		and return the address the user can write data to.
 *
 *    - if no:  Then return NULL
 */
void* mymalloc(size_t request_size, char* string, size_t line){
	
	//check to make sure the heap isn't full	
	if(HEAP_SIZE - memory_count < request_size){
		return NULL;
	}

	//find an open space in the heap
	char* open_position = seek_heap(&heap[0], request_size);
	
	//The seek_heap returns NULL if no block can fit the data being requested
	//This is used as an extra layer of error checking when looking for open memory
	//Thus, if no such memory exists, return NULL
	if(open_position == NULL){
		return NULL;
	}
	
	//create a new spot for the new piece of data
	open_position = partition_mem_node(open_position, request_size);
	
	//return a void* ptr to the new memory location
	return (void*)(open_position);
}

void myfree(void* mem_addr, char* string, size_t line){
	
	//ptr that will be used for traversing through the heap
	char* itr = &heap[0];
	
	int i;
	for(i=0; i<mem_node_count; i++){	
	
		//checks to see if the memory address of the data is the same as the on in the heap
		//if the data we are trying to delete is infact a &char that we can write data too, delete it
		if(mem_addr == (itr+sizeof(MemNode*)+1) ){
			//sets the dirty bit of the current node
			((MemNode*)(itr))->dirty_bit = false;
			purge_heap(itr,itr,0);	
			break;
		}
		
		//update itr to the next position in the heap
		size_t displacement = ((MemNode*)(itr))->mem_size + sizeof(MemNode*) + 1;
		itr += displacement;
	}
}

/*
 * Defragment memory when ever we try to free a node
 */

void purge_heap(char* dest, char* mem_addr, int nodes_purged){
	
	//calculate the displacement
	size_t displacement = ((MemNode*)(dest))->mem_size + sizeof(MemNode*) +1;
	
	
	//if there is only one node left, stop recursing
	if(mem_node_count == 1){
		return;
	} 

	//if the current MemNode and the following MemNode are both capabale of being overwritten,
	//run merge nodes
	if( ((MemNode*)(dest))->dirty_bit == false && 
		((MemNode*)(dest+displacement))->dirty_bit == false && 
		(int)((MemNode*)(dest+displacement))->mem_size != 0){	
				
		//printf("d1 size: %d\n",((MemNode*)(dest))->mem_size);
		//printf("d1 dirty: %d\n",((MemNode*)(dest))->dirty_bit);
		//printf("d2 size: %d\n",((MemNode*)(dest+displacement))->mem_size);
		//printf("d2 dirty: %d\n",((MemNode*)(dest+displacement))->dirty_bit);

		//changed dest to mem_addr
		//printf("MEM_SIZE + DIS:%d\n", ((MemNode*)(dest+displacement))->mem_size);
	
		//merge the size of the two nodes in the left one	
		((MemNode*)(dest))->mem_size += ((MemNode*)(dest+displacement))->mem_size+sizeof(MemNode*);
				
		//printf("MEM_SIZE: %d\n", ((MemNode*)(dest))->mem_size);

		//subtract away a memory node
		mem_node_count-=1;
		
		printf("mem_node_count: %d\n", mem_node_count);
		//recurse through until all adjacent nodes merge
		purge_heap(dest, dest+displacement, nodes_purged+1);
	}

}

/*
 * Traverse through the heap to find a memory address that has:
 *     1. No data written to it
 *     2. Enough room to fit the requested size from the malloc request
 *
 * If these conditions are met, return the memory address of the MemNode that 
 * is going to be truncated.
 */
char* seek_heap(char* starting_block, size_t request_size){	
		
	//ptr that will be used for traversing through the heap
	char* itr = starting_block;
	
	int i;
	for(i=0; i<mem_node_count; i++){
		
		//if there is no data written to said position 
		//and theres enough room at the current location
		if( ((MemNode*)(itr))->dirty_bit == false &&
			((MemNode*)(itr))-> mem_size >=request_size){
				
			//return MemNode if there is enough room
			return itr;
		}
		
		//update itr to the next position in the heap
		size_t displacement = ((MemNode*)(itr))->mem_size + sizeof(MemNode*) +1;
		itr += displacement;
	}
	
	//otherwise return null
	return NULL;
}

/*
 * 1. Takes in a MemNode that new data can be written to. 
 * 2. Splits the MemNode into two MemNodes, 1 for the new data, 1 for leftover data.
 * 3. Returns the memory address the user write to.
 */
char* partition_mem_node(char* open_position, size_t request_size){
	
	//store the size of the original block of memory
	size_t old_size = ((MemNode*)(open_position))->mem_size;
	
	//1. update the old memory size with the new request size	
	//2. update the dirty to show that there is data now written to this position
	((MemNode*)(open_position))->mem_size = request_size;
	((MemNode*)(open_position))->dirty_bit = true;
	
	//Pointer to the malloced position the user requested
	//The value that we are going to return.
	char* write_pos = open_position + sizeof(MemNode*) + 1;

	//create a new MemNode right after the data we are going to return to the user
	//TODO: Check to see if we need to add this +1
	char* new_mem_node = write_pos + request_size;
	((MemNode*)(new_mem_node))->mem_size = old_size - request_size - sizeof(MemNode*);
	((MemNode*)(new_mem_node))->dirty_bit = false;
	
	memory_count += request_size + sizeof(MemNode*);
	mem_node_count += 1;

	return write_pos;

}

/*
 * 1. Cleans the memory in the heap
 * 2. Creates the first memory block that can be written to.
 */
void init_heap(){
	
	//set everything in the array to be 0
	int i;
	for(i=0; i<HEAP_SIZE; i++){
		heap[i]='0';
	}	

	//Look at the fist element in the heap and cast it to a MemNode 
	MemNode* data = (MemNode*)(&heap[0]);
	
	//Write a dirty bit to store that no data is written to this chunk
	data->dirty_bit = false;

	//Store the difference in the heap size and size of MemNode struct.
	//This keeps track of how much data we have left
	data->mem_size = HEAP_SIZE - sizeof(data);

	//update the global heap counter & MemNode counter
	memory_count += sizeof(data);
	mem_node_count += 1;
}

/*
 * 1. Prints the amount of memory allocate & Prints the amount of memory left in the heap
 * 2. Prints out the memory address where data is stored
 * 3. Prints if data is being written to this memory address 
 * 4. Prints out how much data is stored in each MemNode
 */
void print_heap_status(){

	printf("MEMEORY ALLOCATED:\t%d\nMEMORY LEFT:\t\t%d\n\n", memory_count, HEAP_SIZE-memory_count);
	
	int i;
	char* itr = &heap[0];
	for(i=0; i < mem_node_count; i++){
		printf("Data Entry:\t%d\n", i);
		printf("Mem Address:\t%p\n", itr);
		printf("Dirty Bit:\t%d\n", ((MemNode*)(itr))->dirty_bit); 
		printf("Entry Size:\t%d\n\n", ((MemNode*)(itr))->mem_size);
		
		size_t displacement = ((MemNode*)(itr))->mem_size + sizeof(MemNode*) +1;

		itr += displacement;	
	} 
}

