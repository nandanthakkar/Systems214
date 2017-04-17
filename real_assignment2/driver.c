#include "modules.h"
#define ALPHA_SIZE 26;



//main method
int main(){
    
    //basic test:
    char* fileTokens = readfile("./test/testa.txt");
    TokenList* tokenList = split(fileTokens, "./test/testa.txt");

    int amount = tokenList->tok_amount;
    char* filename = tokenList->filename;
    printf("Token Amount:%d, Filename:%s\n", amount, filename); 

    int i;
    for(i=0; i<amount; i++){
        char* token = tokenList->unsort_tokens[i];
        addToken(token, filename);        
    }
    
    printTokenTable();

    return 0;
}
