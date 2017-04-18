#include "modules.h"
#include <errno.h>
#include <stdio.h>

//used to handle input on start up
void onStartUp(int argc, char** argv){
    
    const int SIZE = 1024;
    char input[SIZE];
    char directory[SIZE];

    //if the porper amount of arguments were inserted, clear the buffer, else exit
    if(argc == 3){
        strcpy(input, argv[1]);
        strcpy(directory, argv[2]);
    }
    else{
        printf("ERROR: argument count is wrong.\nToo many or too little arguments\n");
        exit(EXIT_FAILURE);
    }
     
    
    //check to see if the file exists
    if(access(input, F_OK)==0){
        printf("File already exists, would you like to overwrite <y/n>?\n");
        int response = getchar();
        
        //if the user wants to quit, quit
        if(response == 'n'){
            printf("Quiting program.");
            exit(EXIT_SUCCESS);
        }
    }
    //otherwise, the user continues
     
    //check to see if the reading file is a directory or a file
    //create reference to directory and directory entery
    DIR* dir;
    struct dirent* entry;

    if(!(dir = opendir("./"))){
       
        if(errno == ENOTDIR){
            
            

        }
        else{
            perror("ERROR: Couldn't open directory, directory doesn't exist.\n");
            exit(EXIT_FAILURE);
        }
     }


    if(!(entry = readdir(dir))){
        perror("ERROR: Couldn't read directory.\n");
        exit(EXIT_FAILURE);
        
    }
    
    do{
        //check to see if the entry is a directory
        if(entry->d_type == DT_DIR){
            printf("input is directory");
        }
        //check to see if the entry is a regular file
        else if(entry->d_type == DT_REG){
            printf("input is a reg file");
        }
    
    }
    while(entry = readdir(dir));
    perror("ERROR: Counldn't read input as file or directory.\n");
    exit(EXIT_FAILURE);
}

//main method
int main(int argc, char** argv){
    
    onStartUp(argc, argv);
    
    //compare_str("this", "toast");
    return 0;

}
