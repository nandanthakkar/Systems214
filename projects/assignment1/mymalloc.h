/*
 * Authors: Douglas Rudolph, Brandon Yu
 * File: mymalloc.h
 * Course: Systems Programming
 */
#include <stdio.h>

//project function definitions
#define malloc( x ) mymalloc( x, __FILE__, __LINE__ )
#define free( x ) myfree( x, __FILE__, __LINE__ )

//heap size constant
#define HEAP_SIZE 5000

//bool datatype declaration
typedef enum _bool{false, true} bool;

//struct type that keeps track of all the differnet mem elements that are malloced
typedef struct _MemNode{
	size_t mem_size;
	bool dirty_bit;
}MemNode;

//char array that acts as a heap
//FUTURE REFERENFCE: we used char because char is 1 byte
static char heap[HEAP_SIZE];

//variable that keeps track of how much data is left in the heap
static size_t memory_count = 0;

//variable that keeps track of how many MemNodes exists in the heap
static int mem_node_count = 0;



//function definition for mymallloc
void* mymalloc(size_t request_size, char* string, size_t line);

//function definition for mymalloc's free
void myfree(void* mem_addr, char* string, size_t line);

//initializes the heap
void init_heap();

//function that searches through heap seeking for a MemNode 
//that can be partitioned to fit a new MemNode
char* seek_heap(char* starting_block, size_t size);

//function that performs the memory manipulation on a MemNode to split one MemNode into 2
char* partition_mem_node(char* open_position, size_t request_size);

//utterly destroys a MemNode
void purge_heap(char* dest, char* mem_addr, int nodes_purged);

//prints out all the information known about the heap
void print_heap_status();

