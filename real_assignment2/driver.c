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

    //if the token was not in the list, create a token and add it to the hashtable

    if(token_table[index] == NULL){
        //token_table[index] =
    }

} 


int main(){
    
    //basic test:
    char* fileTokens = readfile("../test/testa.txt");
    TokenList* tokenList = split(fileTokens, "../test/testa.txt");

    int amount = tokenList->tok_amount;
    char* filename = tokenList->filename;
    printf("Token Amount:%d, fileame:%s\n", amount, filename); 
   
     

    int i;
    for(i=0; i<amount; i++){

        char* token = tokenList->unsort_tokens[i];
        printf("[%d]: %s\n", i, token);
    
        HashToken* HT = createHashToken(token, filename);
    }
    
    return 0;
}
