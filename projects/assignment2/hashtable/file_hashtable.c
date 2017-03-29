#include "hashtable.h"

TokenNode* create_token_node(char* token_val){
    //malloc room for a token
    TokenNode* node = (TokenNode*) malloc(sizeof(TokenNode));
    
    node->next = NULL;
    
    //malloc room for the string
    node->token_txt = (char*) malloc(sizeof(char)*(strlen(token_val)+1));
    
    strcpy(node->token_txt, token_val);

    return node;
}

FileHash* create_filehash(char* filename, char** tokens){
    //TODO: get rid of file extesion 
    
    FileHash* node = (FileHash*) malloc(sizeof(FileHash));
    node->filename = (char*)malloc(sizeof(char)*(strlen(filename)+1));
    strcpy(node->filename, filename);    
    
    //copy the location of the token list from split into the hashtable
    node->token_list = tokens;
    
    //set the next file to null
    node->next = NULL;

    return node;
}

int hash_id(char c){
    if(isalpha(c))    
        return (int)('a'-c);
    
    perror("The file being inserted doesn't start with a letter");
    exit(EXIT_FAILURE);
}

void put_filehash(char* filename, char** tokens){
   
    //check to make sure the filename works
    if(filename == NULL){
        perror("put(char* filename, char**tokens)\nFile name was null\n");
        exit(EXIT_FAILURE);
    }
        
    //get hash index
    int index = hash_id(filename[0]);
    
    //if there are no files added to the index list, add the first
    if(file_table[index] == NULL){
        printf("0\n");
        file_table[index] = create_filehash(filename, tokens);
    }
    
    //otherwise, insert alphabetically based on file name and insert
    else{
        FileHash* ptr = file_table[index];
        
       
        //checks for all cases in the middle of the list
        for(; ptr->next != NULL; ptr = ptr->next){
            
            //check if the next word and the 
            if(strcmp(filename, ptr->filename)>0 &&
               strcmp(filename, ptr->next->filename)<0){
                
                FileHash* temp = ptr->next;
                ptr->next = create_filehash(filename, tokens);
                ptr->next->next = temp;
                
                return;        
            }
            else if(strcmp(filename, ptr->next->filename) == 0){

                //todo: merge char** in ptr->next with the current node
                

                //return
            }
        }
        
        //insert second node
        if(strcmp(filename, file_table[0]->filename) == 0){
            //merge 
        }
        else if(strcmp(file_table[0]->filename, filename) > 0){
            FileHash* temp = file_table[index];
            file_table[index] = create_filehash(filename, tokens);
            file_table[index] -> next = temp;
            
        }
        else if(strcmp(file_table[0]->filename, filename) < 0){
            file_table[index]->next = create_filehash(filename, tokens);
        }

        //if we get here, there is only 1 element in the list, thus it either goes
        //at the end, or the tokens get merged into the first node    
    }

}

int main(){
    
    put_filehash("ac.txt", NULL);
    put_filehash("aa.txt", NULL);
    put_filehash("ab.txt", NULL);
    printf("%s\n", file_table[0]->filename);
    printf("%s\n", file_table[0]->next->filename); 
    printf("%s\n", file_table[0]->next->next->filename); 
    return 0;
}



