#ifndef HEADER
#define HEADER

#include <string.h>
#include <ctype.h>

#include <stdio.h>
#include <stdlib.h>

#endif

//GLOBAL BOOL TYPE
typedef enum _bool{false, true} bool;

//Used right after splitting data from a file
typedef struct _TokenData{
    char** unsort_tokens;
    int tok_amount;
}TokenList;

//Used as a data type to store the token count within files
typedef struct _token_node{
    char* token;
    int token_frequency;
    char* filename;
    struct _token_node* next;
}TokenNode;

typedef struct _FileHash{
    char* filename;         //name of file
    TokenList* tokens;
    struct _FileHash* next; //next file that starts with the same character
} FileHash;

//Used for creating a Keyset in file_hashtable.c
typedef struct _filename{
    char* filename;
    struct _filename* next; 
}FileName;



//function that compares if a string is larger based on the alphanumeric value
int compare_str(char* a, char* b);

//function that sorts Tokens from a TokenData* based on the alphanumeric compare function
TokenNode* sort(TokenList* data, int SIZE, char* filename);

//merges the tokens from a file when they share the same name
TokenList* merge_data(TokenList* a, TokenList* b);


//Set of functions used to create each struct type
TokenNode* create_token_node(char* token, int token_freq, char* filename);
FileName* create_keyset_elem(char* filename);
FileHash* create_filehash(char* filename, TokenList* token_list);
TokenList* create_token_data(char** unsort_tokens, int tok_amount);
