#include <stdio.h>
#include <stdlib.h>

//boolean types
typedef enum _bool{false=0, true=1} bool;

//HashNode, data type stored in the hashtable
typedef struct _HashNode{
	char* filename;
	int token_count;
	struct _HashNode* next;	
}HashNode;

//will resize as the hashtable resizes
HashNode tok_table[100];

//linked list that stores the keys to the hashtable in alphanumeric order
static HashNode* keyset_root;

//function to walk through the file system
void stroll_through_files(char* root_dir);

//function that reads the file
void read_files(char* filepath);

//goes through 'tok_table' and exports the data to xml
void export_to_xml();

