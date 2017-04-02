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
#include "modules.h"

#endif

void file_system_waltz(const char* dir_name);
TokenList* split(char* str);
char* readfile(char* filepath);
unsigned long long int fsize(char* filepath);
TokenList* create_token_data(char** unsort_tokens, int tok_amount);
