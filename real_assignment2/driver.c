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
   
    //if the directory can't be read, try to open a file
    if(!(dir = opendir(directory))){
       
        //if the error recorded is "Error Not Directory", then check to see if 
        //module to be read is a file
        if(errno == ENOTDIR){
            FILE* fp = fopen(directory, "r");
            
            //if file is null, leave
            if(!fp){
                printf("ERROR: Couldn't open the file, file doesn't exist.\n");
            }
            //otherwiese the file exists
            else{
                //read and get it as a string
                char* fileTokens = readfile(directory);

                //get all the tokens as a list and store the filename
                TokenList* tokenList = split(fileTokens, entry->d_name);

                int amount = tokenList->tok_amount;
                char* filename = tokenList->filename;

                int i;
                for(i=0; i<amount; i++){
                    char* token = tokenList->unsort_tokens[i];
                    addToken(token, filename);        
                }
               
                FILE* outputFile = fopen(input, "w+");
                writeToXML(outputFile);
            }
        }
        else{
            printf("ERROR: Couldn't open directory or file, doesn't exist.\n");
            exit(EXIT_FAILURE);
        }
    }
    //if the directory does exist, read the directory
    else{
        //if it didn't throw an error, check to see if the directory could be read 
        if(!(entry = readdir(dir))){
            printf("ERROR: Couldn't read directory.\n");
            exit(EXIT_FAILURE);
        }
        
        //if the directory was able to be read, read dir
        listdir(directory,0);

        FILE* outputFile = fopen(input, "w+");
        writeToXML(outputFile);
    }
}

//main method
int main(int argc, char** argv){
    
    onStartUp(argc, argv);
    
    //compare_str("this", "toast");
    return 0;

}
