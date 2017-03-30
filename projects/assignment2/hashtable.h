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

static FileName* keyset;
static FileHash* file_table[26];

