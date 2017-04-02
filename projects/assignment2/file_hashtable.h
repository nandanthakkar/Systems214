/*
 * AUTHOR:    Douglas Rudolph
 * FILE:      HashTable.h
 * COURSE:    Systems Programming 214
 * PROFESSOR: Dr. Fransisco
 */

//If libraries are not included, include them
#ifndef HEADER
#define HEADER
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "modules.h"
#include "file_io.h"

#endif



extern FileName* keyset;
extern FileHash* file_table[26];

// create functions for all structs
TokenNode* create_token_node(char* filename);
FileName* create_keyset_elem(char* filename);
FileHash* create_filehash(char* filename, TokenData* token_list);

//File Hashtable functions
int hash_id(char c);
void append_file_to_keyset(char * filename);
void put_filehash(char* filename, TokenData* token_list);



TokenNode* sort(TokenData* data, int SIZE);
int compare_str(char* a, char* b);

