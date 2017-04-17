#include "modules.h"
#define ALPHA_SIZE 26;

//TODO: Ensure to add data to xml file properly
void writeToXML(){
    
    printf("<?xml version=\"1.0\" encoding=\"UTF-8\"?>");
    printf("<fileIndex>\n"); 
    
    //loop through alphabet
    int i = -1;
    for(i=0; i<26; i++){ 
        //loop through tokens in hashtable
        HashToken* itr = NULL;
        for(itr = token_table[i]; itr!=NULL; itr=itr->next){
            //loop through files in each token
            
            printf("\t<word text=\"%s\">\n", itr->token); 
            
            FileData* ptr = NULL;
            int count=0;
            
            for(ptr=itr->head_fd; ptr!=NULL; ptr=ptr->next_fd, count++){
                printf("\t\t<file name=\"%s\">%d</file>\n",ptr->filename, ptr->token_count);
            }
            printf("\t</word>\n");
        }
    }

    printf("</fileIndex>");
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
    
    writeToXML();
    return 0;
}
