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
#include "file_io.h"
#endif

typedef struct _filehash{
    char* filename;         //name of file
    TokenData* tokens;
    struct _filehash* next; //next file that starts with the same character
} FileHash;

typedef struct _filename{
    char* filename;
    struct _filename* next; 
}FileName;

typedef struct _token_node{
    char* token;
    struct _token_node* next;
    int count;
}TokenNode;

extern FileName* keyset;
extern FileHash* file_table[26];

int hash_id(char c);
void append_file_to_keyset(char * filename);
TokenNode* create_token_node(char* filename);
FileName* create_keyset_elem(char* filename);
FileHash* create_filehash(char* filename, TokenData* token_list);
TokenNode* sort(TokenData* data, int SIZE);
int compare_str(char* a, char* b);
void put_filehash(char* filename, TokenData* token_list);

