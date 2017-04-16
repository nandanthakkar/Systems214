#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//boolean type
typedef enum bool{false, true}bool;

//stores filename, the token, and the token count
typedef struct _filedata{
    char* filename;
    char* token;
    int token_count;
    
}FileData;

//keeps track of token, File Data linked list, and refernce to next token in token table
typedef struct _hashtoken{
    char* token;
    FileData* next_fd; 
    struct _hashtoken* next;
}HashToken;


//TODO: Rename to FileTokens
typedef struct _TokenList{
    int tok_amount;
    char** unsort_tokens;
    char* filename;
}TokenList;

TokenList* create_token_list(int tok_amount, char** unsort_tokens, char* filename);


int compare_str(char* a, char* b);


TokenList* split(char* str, char* filename);


unsigned long long int fsize(char* filepath);


char* readfile(char* filepath);
