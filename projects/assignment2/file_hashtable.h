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

//File Hashtable functions
int hash_id(char c);
void append_file_to_keyset(char * filename);
void put_filehash(char* filename, TokenList* token_list);
