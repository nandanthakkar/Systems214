#ifndef HEADER
#include "file_io.h"
#include "file_hashtable.h"
#endif

int main(){
    //1. Go through file system
    //  - Walks through the filesystem,
    //  - copies all the tokens from the file
    //  - stores it in a hashtable, TODO: debug 'put_filehash'
    char* dir;
    file_system_waltz("./test_files");

    //loop over the keyset and get the data with the tokens 
    FileName* ptr;
    for(ptr = keyset; ptr!=NULL; ptr=ptr->next){
        printf("Filename: %s\n", ptr->filename);

        //TokenNode = sorted the tokenlist
        //for loop over token Nodes
        //  hash token nodes
    }   

    //4. Export data to XML

	return 0;
}

/*
 * Purpose: Handles what the program should do on load up 
 *
 * Params: 1. argc:   Argument count that is sent was from main
 *         2. argv**: The actual arguments that were typed in on the command line 
 *                    when running the program
 *
 * Return Type: void
 */
void onLoadUp(int argc, char** argv){
    
    //warn the user there aren't enough arguments
    if(argc <=2){
        perror("ERROR: Not enough arguments on startup.");
    }
    
    //if there are the correct amount of arguments
    else if(argc == 3){
       
        //store a global instance of a the current working directory
        //store_cwd(); 
        printf("CWD: %s\n", CWD);

        //store a global instance of the inverted-index filename 
        //store_inverted_index_filename(argv[1]);
        printf("XML_FILE: %s\n", XML_FILE_NAME); 
             
        //store a global instance of the folder or file we are traversing through
        //store_root_descriptor(argv[2]);   
        printf("ROOT_DES: %s\n", ROOT_DESCRIP);

    }

    //otherwise there are too many arguments
    else{
        perror("ERROR: Too many arguments on startup.");
    }
        
}

