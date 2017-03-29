/*
 * Author: Douglas Rudolph
 * File: filesystem.c
 * Course: Systems Programming
 * Assignment: Recursive Indexer
 */

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


/* 
 * Purpose: 1. Used to walk through the file systems starting from a certain directory.
 *          2. Updates the global directory varibles to keep track of what file we are 
 *             working through.
 *
 * Params: Root directory name
 *
 * Return Type: void
 */
static void file_system_waltz(const char* dir_name){

    DIR * d;

    // Open the directory specified by "dir_name".

    d = opendir (dir_name);

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n", dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while(true) {
        struct dirent * entry;
        const char * d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
        
        // Print the name of the file and directory. 
        // replace with reading a file
        printf ("%s/%s\n", dir_name, d_name);
        
        if (entry->d_type & DT_DIR) {

            /* Check that the directory is not "d" or d's parent. */
            
            if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,
                                        "%s/%s", dir_name, d_name);
                printf ("%s\n", path);
                if (path_length >= PATH_MAX) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
                /* Recursively call "list_dir" with the new path. */
                file_system_waltz(path);
            }
	    }
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

/*
 * Purpose: Store a global instance of the current working directory
 *
 * Params: None 
 *
 * Return Type: void
 *
 */
void store_cwd(){
    //store a global instance  current working directory,
    char temp_cwd[1024];            
    getcwd(temp_cwd, sizeof(temp_cwd));
    
    if(temp_cwd != NULL){
       strcpy(CWD, temp_cwd);
    }
}

/*
 * Purpose: Stores the name of the xml file we are going to store data to at a global level 
 *
 * Params: 1. filename: the name of the xml file we are going to store data too
 *
 * Return Type: void
 *
 */
void store_inverted_index_filename(char* filename){
    strcpy(XML_FILE_NAME, filename);
}

/*
 * Purpose: Stores a global instance of the directory or file where tokens are going to be read
 *
 * Params: 1. root_descrip: name of folder or directory
 * 
 * Return Type: void
 *
 */
void store_root_descriptor(char* root_descrip){
    strcpy(ROOT_DESCRIP,root_descrip); 
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
        store_cwd(); 
        printf("CWD: %s\n", CWD);

        //store a global instance of the inverted-index filename 
        store_inverted_index_filename(argv[1]);
        printf("XML_FILE: %s\n", XML_FILE_NAME); 
             
        //store a global instance of the folder or file we are traversing through
        store_root_descriptor(argv[2]);   
        printf("ROOT_DES: %s\n", ROOT_DESCRIP);

    }

    //otherwise there are too many arguments
    else{
        perror("ERROR: Too many arguments on startup.");
    }
        
}

int main(int argc, char** argv){
   
    //loads constants on start up of the program
    onLoadUp(argc, argv); 
}
