#ifndef HEADER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "project.h"
#include <sys/stat.h>
#endif

char** split(char* str);
char** _sort_split(char** tokens);
char* readfile(char* filepath);
unsigned long long int fsize(char* filepath);


