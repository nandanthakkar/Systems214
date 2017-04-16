#include "modules.h"
#define ALPHA_SIZE 26;

//hash table where all tokens will be stored
HashToken* token_table[26];

void addToken(char* token, char* filename){
    
    if(token == NULL){
        perror("ERROR - addToken: token is NULL");
        exit(EXIT_FAILURE);
    }
    else if(filename == NULL){
        perror("ERROR - addToken: filename is NULL");
        exit(EXIT_FAILURE);
    }

    //get hashid of index
    int index = hashId(token[0]);
    HashToken* itr;
    
    //loop through mapped token_table index and see if the token is in the list
    for(itr = token_table[index]; itr!=NULL; itr = itr->next){
        //if the token is in the list
        if(strcmp(itr->token, token) == 0){

            //check to see if the file name is in the filename list
            FileData* fileItr;
            for(fileItr = itr->head_fd; fileItr!=NULL; fileItr = fileItr->next_fd){
                //if the file is already in the list
                if(strcmp(fileItr->filename, filename)==0){
                    fileItr->token_count++;
                    return;
                }      
            }
        }
    }

    //if there at this index in the hashtable, add to the hashtable and return
    if(token_table[index] == NULL){
        token_table[index] = createHashToken(token, filename);
        return;
    }

    //if there are token is in the hastable, but the filename isn't
    else{
        HashToken* ptr=NULL;
        
        //loop over the table to fin token
        for(ptr = token_table[index]; ptr!=NULL; ptr = ptr->next){
            //if the token is in the list, add the file name is different
            if(strcmp(ptr->token, token)==0){
                 
                FileData* itr = NULL;

                //loop through the files
                for(itr=ptr->head_fd; itr!=NULL; itr=itr->next_fd){
                    
                    //append the the list using alphanumerics
                    if(itr->next_fd != NULL &&
                        compare_str(itr->filename, filename)>0 &&
                        compare_str(itr->next_fd->filename, filename)<0){
                        
                        //insert into the middle of the linked list
                        FileData* temp = itr->next_fd;
                        itr->next_fd = createFileData(token, filename, 1);
                        itr->next_fd->next_fd = temp;

                        //done inserting, so just return
                        return;
                    }
                    
                    //if we get to the last position, append to the end and return
                    else if(itr->next_fd == NULL){
                        printf("MADE IT");
                        itr->next_fd = createFileData(token, filename, 1);
                        return;
                    }
                }
            }             
        }
    }

    //if we get here, the token isn't in the hashtable
    //increment to the end of the hashtable and insert
    HashToken* ptr=NULL;
    for(ptr=token_table[index]; ptr->next!= NULL; ptr=ptr->next);
    ptr->next = createHashToken(token, filename);
    

} 

//goes through all the tokens in the token table and prints out the data
void printTokenTable(){
    //loop through alphabet
    int i = -1;
    for(i=0; i<26; i++){
        
        printf("INDEX: [%c]\n", 'a'+i);

        //loop through tokens in hashtable
        HashToken* itr = NULL;
        for(itr = token_table[i]; itr!=NULL; itr=itr->next){
            
            printf("\tToken: %s\n",itr->token);
            
            //loop through files in each token
            FileData* ptr = NULL;
            int count=0;
            for(ptr=itr->head_fd; ptr!=NULL; ptr=ptr->next_fd, count++){
                printf("\t\t%d. Filename: %s\n\t\tTokenCount: %d\n",count, ptr->filename, ptr->token_count);
            }

        }
    }
        
}

//main method
int main(){
    
    //basic test:
    char* fileTokens = readfile("./test/testa.txt");
    TokenList* tokenList = split(fileTokens, "./test/testa.txt");

    int amount = tokenList->tok_amount;
    char* filename = tokenList->filename;
    printf("Token Amount:%d, fileame:%s\n", amount, filename); 

    int i;
    for(i=0; i<amount; i++){
        char* token = tokenList->unsort_tokens[i];
        addToken(token, filename);        
    }
    
    printTokenTable();

    return 0;
}
