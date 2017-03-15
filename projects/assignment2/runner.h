#include <stdio.h>

static enum _bool{false=0, true=1} bool;

struct _HashNode{
	char* filename;
	int token_count;
	_HashNode* next;	
}HashNode;

//will resize as the hashtable resizes
static HashNode tok_table[100];

void stroll_through_files(char* root_dir);

void read_files(char* filepath);

//goes through 'tok_table' and exports the data to xml
void export_to_xml();

