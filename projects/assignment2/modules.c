#include "modules.h"

//generates a hash position in my hash table
int hash_id(char c){
    if(isalpha(c))    
        return (int)(c-'a');
    
    perror("The file being inserted doesn't start with a letter");
    exit(EXIT_FAILURE);
}

int compare_str(char* a, char* b){
   
    int size_a = strlen(a);
    int size_b = strlen(b);
    //gets the min length between two strings
    int LEN=0;
    
    //get the min number
    if(size_a < size_b)
        LEN = size_a;
    else if(size_b < size_a)
        LEN = size_b;
    else
        LEN = size_a;
    
    
    bool same_prefix = true;
    int weight = 0;
    int i=-1;
    for(i=0; i < LEN; i++){

        //if they are both numbers
        if(isdigit(a[i]) && isdigit(b[i])){
            weight += ((int)98+a[i]) - ((int)98+b[i]); 
        }

        //if a is a leter and b is a digit
        else if(!isdigit(a[i]) && isdigit(b[i])){
            weight += (a[i]) - (((int)b[i])+98);
        }
        
        //if a is a digit and b is a letter
        else if(isdigit(a[i]) && !isdigit(b[i])){
            weight += ((int)98+a[i]) - ((int)b[i]); 
        }

        //if they are both chars
        else{
            weight += ((int)a[i]) - ((int)b[i]); 
        }
    
        if(a[i] != b[i] && same_prefix == true){
            same_prefix = false;
        }
    }

    //aka they are the same beginning of the word
    if(same_prefix==true && size_a > size_b){
        return 1;
    } 
    else if(same_prefix==true && size_a < size_b){
        return -1;
    } 

    return weight;
}

//sorts the files and gets the amount of occurrences of each word
TokenNode* sort(TokenList* data, int SIZE, char* filename){
    char** array = data->unsort_tokens;
    int i=0;
    TokenNode* head = NULL;
    
    //token, frequency, filename
    //link the first string into the list
    head = create_token_node(array[i], 1, filename);
    i++;

    //link the second element

    for(;i < SIZE; i++){
        
        TokenNode* ptr = head;
        for(;ptr != NULL; ptr = ptr->next){
            
            //should come before the beginnnig of the list
            if(ptr != NULL && ptr == head && 
                compare_str(array[i], ptr->token) < 0){
                
                TokenNode* temp = head;
                head = create_token_node(array[i], 1, filename);
                head->next = temp;
                ptr = ptr->next;
            }            

            //if they are the same string
            else if(compare_str(array[i], ptr->token)==0 && 
                    strlen(array[i]) == strlen(ptr->token)){
                
                ptr->token_frequency++;
            }
            
            //if we are at the end and we want to append to the end of the list
            else if(ptr->next == NULL && compare_str(array[i], ptr->token)>0){
                ptr->next = create_token_node(array[i], 1, filename);
                ptr = ptr->next;
            }
            else if(ptr->next != NULL && 
                    compare_str(array[i], ptr->token)>0 &&
                    compare_str(array[i], ptr->next->token)<0){
                
               TokenNode* temp = ptr->next;
               ptr->next = create_token_node(array[i], 1, filename);
               ptr->next->next = temp;
               ptr = ptr->next->next;
            }
        }
    }
    
    //return a linked list of nodes that have the proper count and are sorted
    return head;
}

//returns a struct pointer of type FileHash that is malloced
FileHash* create_filehash(char* filename, TokenList* token_list){
    
    FileHash* node = (FileHash*) malloc(sizeof(FileHash));
    node->filename = (char*)malloc(sizeof(char)*(strlen(filename)+1));
    strcpy(node->filename, filename);    
    
    //copy the location of the token list from split into the hashtable
    node->tokens = token_list;

    //set the next file to null
    node->next = NULL;

    return node;
}

TokenList* merge_data(TokenList* a, TokenList* b){
    
    //malloc room for the new token data
    char** new_toks = (char**) malloc(sizeof(char*)*(a->tok_amount + b->tok_amount));
    
    //copy over the old data from TokenList a
    int offset=0;
    int i;

    for(i=0; i < a->tok_amount; i++, offset++){
        new_toks[i] = a->unsort_tokens[i]; 
    }

    //copy over the old data from TokenList b
    for(i=0; i < b->tok_amount; i++){
        new_toks[i+offset] = b->unsort_tokens[i]; 
    }
    
    TokenList* new_data = create_token_data(new_toks, (a->tok_amount + b->tok_amount)); 
    return new_data;
}


FileName* create_keyset_elem(char* filename){
   
    //malloc data for the struct as well the as the filname
    FileName* file_node = (FileName*) malloc(sizeof(FileName)); 
    
    //malloc data for the string
    file_node -> filename = (char*)malloc(sizeof(char)*(strlen(filename)+1));
    strcpy(file_node->filename, filename);
   
    //set the next value in the linked list to null
    file_node->next = NULL; 

    //return the data
    return file_node;
}

TokenNode* create_token_node(char* token, int token_freq, char* filename){
    
    //malloc room for token
    TokenNode* tok = (TokenNode*) malloc(sizeof(TokenNode));

    tok->token = (char*) malloc(sizeof(char)*strlen(token));
    strcpy(tok->token, token);

    //store the token frequency
    tok->token_frequency = token_freq;

    //store the filename
    tok->filename = (char*)malloc(sizeof(strlen(filename)+1));
    strcpy(tok->filename, filename);

    return tok;
}

TokenList* create_token_data(char** unsort_tokens, int tok_amount){
    TokenList* tok = (TokenList*) malloc(sizeof(TokenList));
    
    //store a reference to the unsorted token list
    tok->unsort_tokens = unsort_tokens;
    //store the amount of tokens from the file
    tok->tok_amount = tok_amount;

    return tok;
}



