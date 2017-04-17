#include "modules.h"
#define ALPHA_SIZE 26;

//TODO: Take for loop from print token_table function and add it here, 
//TODO: Ensure to add data to xml file properly
void writeToXML(){

    

}

//TODO: Need to add function to recurse through filesystem

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
