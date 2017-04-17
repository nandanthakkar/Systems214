#include "modules.h"
#include <errno.h>

#define ALPHA_SIZE 26;

//sort the FileData linked list that is located within each token
FileData* sortFileData(FileData* head){
        
    FileData* newHead = NULL;

    FileData* ptr = NULL;
    for(ptr = head; ptr!= NULL; /*ptr=ptr->next_fd*/){
        
        //if the head is null, add the first element, and disconnect the ptr from the list
        //ADD IF HEAD IS NULL
        if(newHead == NULL){
            newHead = ptr;
            ptr = ptr->next_fd; 
            newHead->next_fd = NULL;
            continue;
        }
        
        //if the token count of a word is greater than the current largest
        //ADD TO FRONT
        else if(newHead->token_count < ptr->token_count){
            FileData* temp = newHead; //store a reference to newHead
            newHead = ptr; //make newHead equal to the new larger ptr
            ptr = ptr->next_fd;//make ptr move forward
            newHead->next_fd = temp;// link back together the sorted list

            continue;
        }

        else if(newHead->token_count == ptr->token_count && 
                compare_str(ptr->filename, newHead->filename) < 0){
            FileData* temp = newHead; //store a reference to newHead
            newHead = ptr; //make newHead equal to the new larger ptr
            ptr = ptr->next_fd;//make ptr move forward
            newHead->next_fd = temp;// link back together the sorted list

            continue;
        }
        
        //ADD TO CENTER & END
        else{
            FileData* itr = NULL;
            for(itr = newHead; itr!=NULL; itr=itr->next_fd){
                
                //if the token frequency is greater than the head of the
                //FREQUENCY MIDDLE
                if(itr->next_fd != NULL &&
                        itr->token_count > ptr->token_count &&
                        ptr->token_count > itr->next_fd->token_count){
                   
                    FileData* temp = itr->next_fd;
                    itr->next_fd = ptr;
                    ptr = ptr->next_fd;
                    itr->next_fd->next_fd= temp;
                    itr = itr->next_fd->next_fd;

                    break;
                }
                
                //else if the token frequency is the same
                //ADD TO MIDDLE (FRONT OF FREQUENCY LIST)
                else if(itr->next_fd!= NULL && 
                        itr->next_fd->token_count == ptr->token_count &&
                        compare_str(ptr->filename, itr->next_fd->filename) < 0){
                   
                    FileData* temp = itr->next_fd;
                    itr->next_fd = ptr;
                    ptr = ptr->next_fd;
                    itr->next_fd->next_fd= temp;
                    itr = itr->next_fd->next_fd;

                    break;   

                }
                //add to end
                else if(itr->next_fd== NULL){
                    itr->next_fd = ptr;
                    ptr = ptr->next_fd;
                    itr= itr->next_fd;
                    itr->next_fd = NULL;
                    break;
                }
            }
        }
    }
    
    return newHead;
}


//main method
int main(int argc, char** argv){
    
    FileData* one = createFileData("banana", "can", 11);
    FileData* two = createFileData("banana", "coo", 5);
    FileData* three = createFileData("banana", "coe", 5);
    FileData* four = createFileData("banana", "cap", 5);
    FileData* five = createFileData("banana", "code", 5);
    FileData* six = createFileData("banana", "con", 5);
    FileData* seven = createFileData("banana", "coool", 5);

    one->next_fd = two;
    two->next_fd = three;
    three->next_fd = four;
    four->next_fd = five;
    five->next_fd = six;
    six->next_fd = seven;

    printf("BEFORE:\n");
    FileData* itr;
    for(itr=one; itr!=NULL; itr=itr->next_fd){
        printf("%s %d\n", itr->filename, itr->token_count);
    }
    

    printf("AFTER:\n");
    FileData* list = sortFileData(one);
    
    for(itr= list; itr!=NULL; itr=itr->next_fd){
        printf("%s %d\n", itr->filename, itr->token_count);
    }

    /*
    listdir("./test", 0);
    writeToXML();
    */
    return 0;

}
