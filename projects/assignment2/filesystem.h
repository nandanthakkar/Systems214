#ifndef FILE_SYS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
// "readdir" etc. are defined here. 
#include <dirent.h>
// limits.h defines "PATH_MAX". 
#include <limits.h>

#include "globals.h"
#include "project.h"
#include "file_io.h"
#endif

static void file_system_waltz(const char* dir_name);
void store_cwd();
void store_inverted_index_filename(char* filename);
void store_root_descriptor(char* root_descrip);
void onLoadUp(int argc, char** argv);


