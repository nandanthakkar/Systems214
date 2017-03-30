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

TokenNode* create_token_node(char* filename){
    
    //create token
    TokenNode* tok = (TokenNode*) malloc(sizeof(TokenNode));
    
    //store string
    tok->token = (char*)malloc(sizeof(strlen(filename)+1));
    strcpy(tok->token, filename);
    
    tok->count = 1;

    return tok;
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

int compare_str(char* a, char* b){
   
    int size_a = strlen(a);
    int size_b = strlen(b);
    
    //gets the min length between two strings
    int LEN=0;
    
    //get the min number
    if(size_a != size_b){
        LEN = (size_a < size_b)?size_a:size_b;
    }
    else{
        LEN = size_a;
    }
     
    int weight = 0;

    int i=-1;
    for(i=0; i < LEN; i++){

        //if they are both numbers
        if(isdigit(a[i]) && isdigit(b[i])){
            weight += ((int)100+a[i]) - ((int)100+b[i]); 
        }

        //if a is a leter and b is a digit
        else if(!isdigit(a[i]) && isdigit(b[i])){
            weight += ((int)a[i]) - ((int)100+b[i]);
        }
        
        //if a is a digit and b is a letter
        else if(isdigit(a[i]) && !isdigit(b[i])){
            weight += ((int)100+a[i]) - ((int)b[i]); 
        }

        //if they are both chars
        else{
            weight += ((int)a[i]) - ((int)b[i]); 
        }
    }

    //LOOP THROUGH TO THROW THE WAIT OFF
    if(size_a > size_b){
        for(; i<size_a; i++){
                
            //if they are both numbers
            if(isdigit(a[i]) && isdigit(b[i])){
                weight += ((int)100+a[i]) - 0; 
            }

            //if a is a leter and b is a digit
            else if(!isdigit(a[i]) && isdigit(b[i])){
                weight += ((int)a[i]) - 0;
            }
            
            //if a is a digit and b is a letter
            else if(isdigit(a[i]) && !isdigit(b[i])){
                weight += ((int)100+a[i]) - 0; 
            }

            //if they are both chars
            else{
                weight += ((int)a[i])-0; 
            }
        }
    }
    else if(size_b > size_a){
        
        for(; i<size_b; i++){
                
            //if they are both numbers
            if(isdigit(a[i]) && isdigit(b[i])){
                weight += 0 -((int)100+b[i]) ; 
            }

            //if a is a leter and b is a digit
            else if(!isdigit(a[i]) && isdigit(b[i])){
                weight += 0 - ((int)b[i]);
            }
            
            //if a is a digit and b is a letter
            else if(isdigit(a[i]) && !isdigit(b[i])){
                weight += 0 - ((int)100+b[i]); 
            }

            //if they are both chars
            else{
                weight += 0 - ((int)b[i]); 
            }
        }
    }

    return weight;
}

void sort(char** array, int SIZE){
    char** sort_arr;
    int i=0;
    TokenNode* head = NULL;
    
    //link the first string into the list
    head = create_token_node(array[i]);
    i++;

    //link the second element

    for(;i < SIZE; i++){
        
        TokenNode* ptr = head;
        for(;ptr != NULL; ptr = ptr->next){
            
            //should come before the beginnnig of the list
            if(ptr != NULL && 
                compare_str(ptr->token,array[i]) > 0){
                
                TokenNode* temp = head;
                head = create_token_node(array[i]);
                head->next = temp;
            }            

            //if they are the same string
            else if(compare_str(array[i], ptr->token)==0 && 
                    strlen(array[i]) == strlen(ptr->token)){
                ptr->count++;
            }
        }
    }
    
    printf("%s\n",head->token);
    printf("%s\n", head->next->token);

}

int main(){
    
    char* arr[] = {"ad0","ad"};
    //sort(arr, 2);
    
    printf("a = ad0, b = ad\n output: %d\n\n", compare_str(arr[0], arr[1]));
    printf("a = ad, b = ad0\n output: %d\n", compare_str(arr[1], arr[0]));
    
    return 0;
}

