#include "file_hashtable.h" 

//initialzies the head ptr for the  keyset to null
FileName* keyset = NULL;

//global initialization of the file hashtable
FileHash* file_table[26];

//function to append a filename to they keyset
//(NOTE*): file names are not sorted alphabetically
void append_file_to_keyset(char* filename){
    //if empty, add the the first filename
    if(keyset == NULL){
        keyset = create_keyset_elem(filename);
    }
    //else append (we will sort later using another sort function)
    else{
        FileName* ptr = keyset;
        for(; ptr->next != NULL; ptr = ptr->next);
        
        //append the new filename
        ptr->next = create_keyset_elem(filename);
    }
}

//generates a hash position in my hash table
int hash_id(char c){
    if(isalpha(c))    
        return (int)(c-'a');
    
    perror("The file being inserted doesn't start with a letter");
    exit(EXIT_FAILURE);
}

/*
 * char** tokens readfile(filename)// read tokens from file
 * TokenList data = create_token_data(token, amount) //store the token into struct
 * put_filehash(filename) //put data into hashtable
 * extract_data() //loop through keyset and get all nodes
 * write to file
 *
 */
void put_filehash(char* filename, TokenList* token_list){
   
    //check to make sure the filename works
    if(filename == NULL){
        perror("put(char* filename, char**tokens)\nFile name was null\n");
        exit(EXIT_FAILURE);
    }
    
    //printf("PUT_FILEHASH: %s\n", filename);

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
           
            //printf("PTR: %s\n", ptr->filename);

            //put a word in between 2 words based on name 
            if(compare_str(filename, ptr->filename)>0 &&
               compare_str(filename, ptr->next->filename)<0){
                
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
