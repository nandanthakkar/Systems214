#include "hashtable.h"
#include "./../file_io.c"


TokenNode* create_token_node(char* token_val){
    //malloc room for a token
    TokenNode* node = (TokenNode*) malloc(sizeof(TokenNode));
    
    node->next = NULL;
    
    //malloc room for the string
    node->token_txt = (char*) malloc(sizeof(char)*(strlen(token_val)+1));
    
    strcpy(node->token_txt, token_val);

    return node;
}

FileHash* create_filehash(char* filename, TokenData* token_list){
    //TODO: get rid of file extesion 
    
    FileHash* node = (FileHash*) malloc(sizeof(FileHash));
    node->filename = (char*)malloc(sizeof(char)*(strlen(filename)+1));
    strcpy(node->filename, filename);    
    
    //copy the location of the token list from split into the hashtable
    node->tokens = token_list;

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

void put_filehash(char* filename, TokenData* token_list){
   
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
        file_table[index] = create_filehash(filename, token_list);
    }
    
    //otherwise, insert alphabetically based on file name and insert
    else{
        FileHash* ptr = file_table[index];
       
        //checks for all cases in the middle of the list
        for(; ptr->next != NULL; ptr = ptr->next){
            
            //put a word in between 2 words based on name 
            if(strcmp(filename, ptr->filename)>0 &&
               strcmp(filename, ptr->next->filename)<0){
                
                FileHash* temp = ptr->next;
                ptr->next = create_filehash(filename, token_list);
                ptr->next->next = temp;
                
                return;        
            }

            //merge tokens if the files share the same name
            else if(strcmp(filename, ptr->next->filename) == 0){

                //todo: merge char** in ptr->next with the current node
                
                FileHash* temp = create_filehash(filename, token_list);
                ptr->tokens = merge_data(temp->tokens, ptr->tokens);
                return;
            }
        }
        
        //insert second node
        if(strcmp(filename, file_table[index]->filename) == 0){
            FileHash* temp = create_filehash(filename, token_list);
            file_table[index]->tokens = merge_data(temp->tokens, file_table[index]->tokens);
            //file_table[index] = merge_data(
        }
        else if(strcmp(file_table[index]->filename, filename) > 0){
            FileHash* temp = file_table[index];
            file_table[index] = create_filehash(filename, token_list);
            file_table[index] -> next = temp;
        }
        else if(strcmp(file_table[0]->filename, filename) < 0){
            file_table[index]->next = create_filehash(filename, token_list);
        }

        //if we get here, there is only 1 element in the list, thus it either goes
        //at the end, or the tokens get merged into the first node    
    }

}

int main(){
    
    char* str = readfile("./aa.txt");
    TokenData* a = split(str);
    
    char* str2 = readfile("./ab.txt");
    TokenData* b = split(str2);
    
    char* str3 = readfile("./ac.txt");
    TokenData* c = split(str3);

    put_filehash("ac.txt", c);
    put_filehash("aa.txt", a);
    put_filehash("ab.txt", b);
    printf("%s\n", file_table[0]->filename);
    printf("%s\n", file_table[0]->next->filename); 
    printf("%s\n", file_table[0]->next->next->filename); 
    return 0;
}



