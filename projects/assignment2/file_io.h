#ifndef HEADER
#define HEADER
#include <ctype.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <limits.h>

#include "globals.h"
#endif

//boolean types
typedef enum _bool{false, true} bool;

typedef struct tokens{
    char** unsort_tokens;
    int tok_amount;
}TokenData;

static void file_system_waltz(const char* dir_name);

void onLoadUp(int argc, char** argv);

TokenData* split(char* str);

char* readfile(char* filepath);

unsigned long long int fsize(char* filepath);

TokenData* create_token_data(char** unsort_tokens, int tok_amount);

TokenData* merge_data(TokenData* a, TokenData* b);


