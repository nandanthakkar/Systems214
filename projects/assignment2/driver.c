#ifndef HEADER
#include "file_io.h"
#include "hashtable.h"
#endif

int main(){
    //1. Go through file system
    //  - Walks through the filesystem,
    //  - copies all the tokens from the file
    //  - stores it in a hashtable, TODO: debug 'put_filehash'
    char* dir;
    file_system_waltz("./test_files");

    //loop over the keyset
 
    FileName* ptr;
    for(ptr = keyset; ptr!=NULL; ptr=ptr->next){
        printf("Filename: %s\n", ptr->filename);
    }   

    //4. Export data to XML

	return 0;
}
