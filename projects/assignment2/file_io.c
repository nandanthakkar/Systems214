#include "file_io.h"
#include "file_hashtable.h"

/*
 * Purpose: 1. Return a 2D-array of strings that are in the set of Alphanumeric strings.
 *          - Alphanumeric is defined as a string that is made of characters and numbers
 *            that MUST START with a alphabetic character.
 * 
 * Params: str: The string that will be read
 *
 * Return Type: char**: The array of alphanumeric strings
 *
 * Example: "hello, $my*name 1s albert." => "['hello', 'my', 'name', 's', 'albert']"
 */
TokenList* split(char* str){
    
    if(str == NULL){
        printf("STRING IS NULL:");
        exit(EXIT_FAILURE);
    }
    int inter_tab[strlen(str)][2]; //array of ints that represent the starting and ending points of alphenumerics
    int word_count = 0;//stores how many alphanumerics have been found

    bool inword = false; //boolean telling us if the loop is currently looking inside a word
    int i;       //iteratirng variable

    //loop through the string until the null character is hit
    for(i=0; i < strlen(str); i++){
        //find the beginning of the word
        if(!inword && isalpha(str[i])){
            inword = true;                  // mark were in a word
            inter_tab[word_count][0] = i;   // mark current pos in the string as word start
        }
 
        else if(inword && str[i+1] == '\n' || inword && str[i+1] == '\0'){
            inter_tab[word_count][1] = i+1;   // mark the closing char-pos to the word
            word_count++;                   // increase the word count by 1
            inword = false;                 // mark that we are no longer in a word
        }       

        //find the end of the word
        else if(inword && !isalpha(str[i]) && !isdigit(str[i])){
            inter_tab[word_count][1] = i;   // mark the closing char-pos to the word
            word_count++;                   // increase the word count by 1
            inword = false;                 // mark that we are no longer in a word
        }
    }

    //make the array of strings
    i=-1;
    char** alphas = (char**) malloc(sizeof(char*)*word_count); //create a 2D of strings 
    
    //loop through the indicies found
    for(i=0; i<word_count; i++){
        int interval = inter_tab[i][1]-inter_tab[i][0]; // get the size of the interval
        alphas[i] = (char*) malloc(sizeof(char)*interval+1);  //malloc the room for the string plus character for the null char
        sprintf(alphas[i],"%.*s", interval, str + inter_tab[i][0]); //write the string the alpha array
        //printf("%s\n",alphas[i]); //print it for testing purposes
        //printf("%.*s\n", interval, str + inter_tab[i][0]);//test purposes
    }
    
    return create_token_data(alphas ,word_count); //return struct with tokens and amount
}

//reads data from a file and stores it in a buffer
char* readfile(char* filepath){
    
    //create file pointer to file
    FILE* fp;
    fp = fopen(filepath,"r");
    
    //check to see if file pointer is null, if so end program
    if(fp == NULL){
        perror("void read_file(char* filepath):\n couldn't read file read_file\n NULL file pointer");
        exit(EXIT_FAILURE);
    }
    
    //get the size of the buffer and initialize the buffer to be all 0s
    unsigned long long int filesize = fsize(filepath);
    char* buffer = (char*)malloc(sizeof(char)*filesize); 
    int i=0;
    for(; i<filesize; i++)
        buffer[i] = '\0';

    //copy the string to the buffer
    fread(buffer, sizeof(char), filesize, fp); 

    //close file stream
    fclose(fp);
    
    return buffer;
}

//returns the size of a function
unsigned long long int fsize(char* filepath){
    
    FILE* fp = fopen(filepath, "r");
    fseek(fp, 0, SEEK_END);     // seek to end of file
    int size = ftell(fp);       // get current file pointer
    fseek(fp, 0, SEEK_SET);
    
    return size;
}

/* 
 * Purpose: 1. Used to walk through the file systems starting from a certain directory.
 *          2. Updates the global directory varibles to keep track of what file we are 
 *             working through.
 *
 * Params: Root directory name
 *
 * Return Type: void
 */
void file_system_waltz(const char* dir_name){

    // Open the directory specified by "dir_name".
    DIR* d;
    d = opendir(dir_name);

    /* Check it was opened. */
    if(!d){
        fprintf (stderr, "Cannot open directory '%s': %s\n", dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }

    while(true){
        struct dirent* entry;
        char* d_name;
     
        // "Readdir" gets subsequent entries from "d".
        entry = readdir(d);
        if (!entry) {
            //There are no more entries in this directory, so break
            //out of the while loop. 
            break;
        }
        
        d_name = entry->d_name;
        if(entry->d_type == DT_REG){
            //buffer for path name
            char file_to_read[1024];

            //get the path to the filename as a string
            sprintf(file_to_read,"%s/%s", dir_name, d_name);
            
            //get the file content as a string
            char* file_str = readfile(file_to_read);
            
            //split the file_str into tokens
            TokenList* unsorted_tokens = split(file_str);

            //store tokens in a hashtable
            put_filehash(d_name, unsorted_tokens); 
        }
            
        //if a directory
        if (entry->d_type & DT_DIR) {
            // Check that the directory is not "d" or d's parent.
            if (strcmp (d_name, "..") != 0 && strcmp (d_name, ".") != 0) {
                int path_length;
                char path[PATH_MAX];
 
                path_length = snprintf (path, PATH_MAX,"%s/%s", dir_name, d_name);
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
