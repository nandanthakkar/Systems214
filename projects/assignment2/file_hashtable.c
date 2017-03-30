#include "hashtable.h" 

FileHash* create_filehash(char* filename, TokenData* token_list){
    
    FileHash* node = (FileHash*) malloc(sizeof(FileHash));
    node->filename = (char*)malloc(sizeof(char)*(strlen(filename)+1));
    strcpy(node->filename, filename);    
    
    //copy the location of the token list from split into the hashtable
    node->tokens = token_list;

    //set the next file to null
    node->next = NULL;

    return node;
}


FileName* create_keyset_elem(char* filename){
   
    //malloc data for the struct as well the as the filname
    
    FileName* file_node = (FileName*) malloc(sizeof(FileName)); 
    
    file_node -> filename = (char*)malloc(sizeof(char)*(strlen(filename)+1));
    file_node->next = NULL; 
    
    //copy the string into the struct
    strcpy(file_node->filename,filename);

    return file_node;
}

void append_file_to_keyset(char * filename){
    
    //if empty, add the the first filename
    if(keyset == NULL){
        keyset = create_keyset_elem(filename);
    }  
    //if the new filename is less than the first filename based on strcmp, add to front
    else if(strcmp(filename, keyset->filename) < 0){
        FileName* temp = keyset;
        keyset = create_keyset_elem(filename);
        keyset->next = temp;
        
        return;
    }
    else if(strcmp(filename, keyset->filename) == 0){
        return;
    }
    //if the new filename is greater than the first filename, append to SECOND element
    else if(strcmp(filename, keyset->filename) > 0 && keyset->next == NULL){
        keyset->next = create_keyset_elem(filename); 
        
        return;
    }
    else{
       
        FileName* itr;
        for(itr = keyset; itr->next != NULL; itr = itr->next){
             
            //if they are equal, ignore the filename
            if(strcmp(filename, itr->filename) == 0){
                return;
            }
            
            //append to middle
            if(strcmp(filename, itr->filename) > 0 && strcmp(filename, itr->next->filename)<0){
                FileName* temp = keyset->next;
                itr = create_keyset_elem(filename);
                itr->next = temp;

                return;
            }
        }
        
        
        //if made it past the for loop, we must append to the end
        itr->next = create_keyset_elem(filename);
        return;
    }
}

int hash_id(char c){
    if(isalpha(c))    
        return (int)(c-'a');
    
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
    
    //insert into keyset
    append_file_to_keyset(filename); 

    //if there are no files added to the index list, add the first
    if(file_table[index] == NULL){
        file_table[index] = create_filehash(filename, token_list);
    }
    
    //otherwise, insert alphabetically based on file name and insert
    else{
        FileHash* ptr = file_table[index];
       
        //checks for all cases in the middle of the list
        for(;ptr->next != NULL; ptr = ptr->next){
           
            printf("PTR: %s\n", ptr->filename);

            //put a word in between 2 words based on name 
            if(strcmp(filename, ptr->filename)>0 &&
               strcmp(filename, ptr->next->filename)<0){
                
                FileHash* temp = ptr->next;
                ptr->next = create_filehash(filename, token_list);
                ptr->next->next = temp;
                
                return;        
            }

            //merge tokens if the files share the same name
            else if(strcmp(filename, ptr->filename) == 0){
                FileHash* temp = create_filehash(filename, token_list);
                ptr->tokens = merge_data(temp->tokens, ptr->tokens);
                return;
            }
        }
        
        //insert second node
        if(strcmp(filename, file_table[index]->filename) == 0){
            //merge the data
            FileHash* temp = create_filehash(filename, token_list);
            file_table[index]->tokens = merge_data(temp->tokens, file_table[index]->tokens);
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
    char* str = readfile("./test_files/one/aa.txt");
    TokenData* a = split(str);
    
    char* str2 = readfile("./test_files/aa.txt");
    TokenData* b = split(str2);
    
    put_filehash("bc.txt", a);
    put_filehash("ab.txt", a);
    put_filehash("aa.txt", a);
    put_filehash("zz.txt", a);
    
    //if(keyset->next == NULL)
    //printf("\n\n%s\n", keyset->filename);
    printf("%s\n", keyset->next->filename);
    printf("%s\n", keyset->next->next->filename);
    printf("%s\n", keyset->next->next->next->filename);
    //printf("%s, %d\n", file_table[0]->filename, file_table[0]->tokens->tok_amount);
    // printf("%s\n", file_table[0]->next->filename); 
    return 0;
}



