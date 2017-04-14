#include "token_hashtable.h"

void put_tokenhash(TokenNode* hash){
        
    TokenNode* ptr = head;
    for( ;ptr != NULL; ptr = ptr->next){
        
        //should come before the beginnnig of the list
        if(ptr != NULL && ptr == head && 
           /*compare_str(array[i], ptr->token) < 0)*/{
            
            TokenNode* temp = head;
            //head = create_token_node(array[i], 1, filename);
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
            //ptr->next = create_token_node(array[i], 1, filename);
            ptr = ptr->next;
        }

        else if(ptr->next != NULL && 
                compare_str(array[i], ptr->token)>0 &&
                compare_str(array[i], ptr->next->token)<0){
            
           TokenNode* temp = ptr->next;
           //ptr->next = create_token_node(array[i], 1, filename);
           ptr->next->next = temp;
           ptr = ptr->next->next;
        }
    }

//return a linked list of nodes that have the proper count and are sorted
return head;
}

