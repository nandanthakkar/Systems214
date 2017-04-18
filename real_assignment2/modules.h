#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

//boolean type
typedef enum bool{false, true}bool;

//stores filename, the token, and the token count
typedef struct _filedata{
    char* filename;
    char* token;
    int token_count;
    struct _filedata* next_fd; 
}FileData;

//keeps track of token, File Data linked list, and refernce to next token in token table
typedef struct _hashtoken{
    char* token;
    FileData* head_fd; 
    struct _hashtoken* next;
}HashToken;


//TODO: Rename to FileTokens
typedef struct _TokenList{
    int tok_amount;
    char** unsort_tokens;
    char* filename;
}TokenList;

//token hashtable
HashToken* token_table[26];

// create functions
HashToken* createHashToken(char* token, char* filename);
FileData* createFileData(char* token, char* filename, int token_count);
TokenList* createTokenList(int tok_amount, char** unsort_tokens, char* filename);

//helper functions
int compare_str(char* a, char* b);
TokenList* split(char* str, char* filename);
unsigned long long int fsize(char* filepath);
char* readfile(char* filepath);
int hashId(char c);
void addToken(char* token, char* filename);
void printTokenTable();
void listdir(const char *name, int level);
void writeToXML();
FileData* sortFileData(FileData* head);
