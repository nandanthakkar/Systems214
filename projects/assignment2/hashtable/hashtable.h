/*
 * AUTHOR:    Douglas Rudolph
 * FILE:      HashTable.h
 * COURSE:    Systems Programming 214
 * PROFESSOR: Dr. Fransisco
 */

//If libraries are not included, include them
#ifndef DIRS
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "../project.h"
#endif

typedef struct tok_node{
    char* token_txt;
    struct tok_node* next;
}TokenNode;

typedef struct _filehash{
    char* filename;         //name of file
    char** token_list;
    struct _filehash* next; //next file that starts with the same character
} FileHash;


static FileHash* file_table[26];

