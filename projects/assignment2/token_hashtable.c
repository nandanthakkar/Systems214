#include "token_hashtable.h"

void put_tokenhash(TokenNode* hash){
    
    //breaks program in case there is an error
    if(hash != NULL){
        perror("put_filehash(char* filename, char**tokens)\nFile name was null\n");
        exit(EXIT_FAILURE);
    }

    //position we are going to write
    int index = hash_id(hash->token[0]);
    
    //if there are no files added to the token_table
    //ADDS TO THE BEGINNING OF A LIST
    if(token_table[index] == NULL){
        token_table[index] = hash;
    }
    else{
        TokenNode* ptr=NULL;
        
        for(ptr = token_table[index]; ptr != NULL; ptr = ptr->next){
            
            //If they have the same token, compare frequency, 
            //  if the frequency of the new token is greater, add to front
            //  if the frequency of the new token is less, to back
            //  if the frequency of the new token is the same, append based on alphanumerics
            if(compare_str(hash->token, ptr->token) == 0){
                //TODO: sort based on if token is found    
            }
            
            // if we are in the middle of the array and,
            //    the string we are adding is less than the next token and,
            //    the string we are addign is larger than the current token and,
            else if(ptr->next != NULL && 
                    compare_str(hash->token, ptr->next->token) < 0 &&
                    compare_str(hash->token, ptr->token)>0){
                
                /*                
                 * [a]-> [b]->    
                 * temp -> [b]    
                 * [a]->new       
                 * new -> temp    
                 *                
                 * ========       
                 * RESULT       
                 * ========     
                 * [a]->[new]->[b]->
                 *
                 */
                TokenNode* temp = ptr->next;
                ptr->next = hash;
                ptr->next->next = temp;
                ptr = temp;
            }
            
            // iff we are at the end of the list, and the token is larger, add to end
            else if(ptr->next == NULL &&
                    compare_str(hash->token, ptr->token) > 0){
               
                //set the last element to new token
                ptr-> next = hash;

                //advance the ptr forward
                ptr = ptr->next;

                //leave function
                return;
            }
        }
    }
}
