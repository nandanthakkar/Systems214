#ifndef HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "project.h"
#include <sys/stat.h>
#endif

typedef struct tokens{
    char** unsort_tokens;
    int tok_amount;
}TokenData;

TokenData* split(char* str);
char* readfile(char* filepath);
unsigned long long int fsize(char* filepath);
TokenData* create_token_data(char** unsort_tokens, int tok_amount);
TokenData* merge_data(TokenData* a, TokenData* b);


