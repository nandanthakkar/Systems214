#include "modules.h"
#define ALPHA_SIZE 26


//hash table where all tokens will be stored
HashToken* token_table[ALPHA_SIZE];


int main(){
    
    //basic test:
    char* fileTokens = readfile("");
    TokenList* tokenList = split(fileTokens, "");

    int amount = tokenList->tok_amount;
    char* filename = tokenList->filename;
    printf("Token Amount:%d, fileame:%s\n", amount, filename); 
    
    int i;
    for(i=0; i<amount; i++){
        printf("[%d]: %s\n", i, tokenList->unsort_tokens[i]);
    }

    return 0;
}

