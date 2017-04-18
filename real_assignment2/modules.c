#include "modules.h"

HashToken* createHashToken(char* token, char* filename){
    HashToken* HT = (HashToken*) malloc(sizeof(HashToken));

    HT->token = (char*)malloc((sizeof(char)*strlen(token) + 1));
    strcpy(HT->token, token);

    HT->head_fd = createFileData(token, filename, 1);
    HT->next = NULL;

    return HT;
}

FileData* createFileData(char* token, char* filename, int token_count){

    FileData* FD = (FileData*)malloc(sizeof(FileData));

    FD->token = (char*)malloc((sizeof(char) * strlen(token)+1));
    strcpy(FD->token, token);

    FD->filename = (char*)malloc( (sizeof(char) * strlen(filename)+1));
    strcpy(FD->filename, filename);

    FD->token_count = token_count;
    FD->next_fd=NULL;

    return FD;
}

TokenList* createTokenList(int tok_amount, char** unsort_tokens, char* filename){
    TokenList* newTL = (TokenList*)malloc(sizeof(TokenList));
    
    newTL->tok_amount = tok_amount;
    newTL->unsort_tokens = unsort_tokens;
    
    newTL->filename = (char*)malloc((sizeof(char)*strlen(filename) + 1));
    strcpy(newTL->filename, filename);

    return newTL;
}

//evaluates which string is < or > than one another bases on alphanumerics
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
    for(i=0; i < LEN && same_prefix == true; i++){

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

//get tokens out of string (string comes from a file)
TokenList* split(char* str, char* filename){
    
    if(str == NULL){
        printf("STRING IS NULL:");
        exit(EXIT_FAILURE);
    }
    int inter_tab[strlen(str)][2]; //array of ints that represent the starting and ending points of alphenumerics
    int word_count = 0;//stores how many alphanumerics have been found

    bool inword = false; //boolean telling us if the loop is currently looking inside a word
    int i;       //iteratirng variable

    //loop through the string until the null character is hit
    for(i=0; i < strlen(str); i++){
        //find the beginning of the word
        if(!inword && isalpha(str[i])){
            inword = true;                  // mark were in a word
            inter_tab[word_count][0] = i;   // mark current pos in the string as word start
        }
 
        else if(inword && str[i+1] == '\n' || inword && str[i+1] == '\0'){
            inter_tab[word_count][1] = i+1;   // mark the closing char-pos to the word
            word_count++;                   // increase the word count by 1
            inword = false;                 // mark that we are no longer in a word
        }       

        //find the end of the word
        else if(inword && !isalpha(str[i]) && !isdigit(str[i])){
            inter_tab[word_count][1] = i;   // mark the closing char-pos to the word
            word_count++;                   // increase the word count by 1
            inword = false;                 // mark that we are no longer in a word
        }
    }

    //make the array of strings
    i=-1;
    char** alphas = (char**) malloc(sizeof(char*)*word_count); //create a 2D of strings 
    
    //loop through the indicies found
    for(i=0; i<word_count; i++){
        int interval = inter_tab[i][1]-inter_tab[i][0]; // get the size of the interval
        alphas[i] = (char*) malloc(sizeof(char)*interval+1);  //malloc the room for the string plus character for the null char
        
        //set the temp string buffer to all nulls
        char temp[interval+1];
        int j;
        for(j=0; j< interval+1; j++)
            temp[j]='\0';
        
        sprintf(temp,"%.*s", interval, str + inter_tab[i][0]); //write the string to temp buffer
        
        //make all the characters in the string lowercase
        int l;
        for(l=0; l<strlen(temp); l++){
            temp[l] = tolower(temp[l]);    
        }
        
        //double check that the last element of a word is infact a character
        if(!isalpha(temp[interval-1])){
            temp[interval-1]='\0';
        }

        //copy the lowercase string into the array
        strcpy(alphas[i], temp);

        //printf("%s\n",alphas[i]); //print it for testing purposes
        //printf("%.*s\n", interval, str + inter_tab[i][0]);//test purposes
    }
    
    return createTokenList(word_count, alphas, filename); //return struct with tokens and amount
}

//returns the size of a function
unsigned long long int fsize(char* filepath){
    
    FILE* fp = fopen(filepath, "r");
    fseek(fp, 0, SEEK_END);     // seek to end of file
    int size = ftell(fp);       // get current file pointer
    fseek(fp, 0, SEEK_SET);
    
    return size;
}

//reads data from a file and stores it in a buffer
char* readfile(char* filepath){
    
    //create file pointer to file
    FILE* fp;
    fp = fopen(filepath,"r");
    
    //check to see if file pointer is null, if so end program
    if(fp == NULL){
        perror("void read_file(char* filepath):\n couldn't read file read_file\n NULL file pointer");
        exit(EXIT_FAILURE);
    }
    
    //get the size of the buffer and initialize the buffer to be all 0s
    unsigned long long int filesize = fsize(filepath);
    char* buffer = (char*)malloc(sizeof(char)*filesize); 
    int i=0;
    for(; i<filesize; i++)
        buffer[i] = '\0';

    //copy the string to the buffer
    fread(buffer, sizeof(char), filesize, fp); 

    //close file stream
    fclose(fp);
    
    return buffer;
}

//generates a hash position in my hash table
int hashId(char c){
    if(isalpha(c))    
        return (int)(c-'a');
    
    perror("The file being inserted doesn't start with a letter");
    exit(EXIT_FAILURE);
}

//hash table where all tokens will be stored

void addToken(char* token, char* filename){
    
    if(token == NULL){
        perror("ERROR - addToken: token is NULL");
        exit(EXIT_FAILURE);
    }
    else if(filename == NULL){
        perror("ERROR - addToken: filename is NULL");
        exit(EXIT_FAILURE);
    }

    //get hashid of index
    int index = hashId(token[0]);
    HashToken* itr;
    
    //loop through mapped token_table index and see if the token is in the list
    for(itr = token_table[index]; itr!=NULL; itr = itr->next){
        //if the token is in the list
        if(strcmp(itr->token, token) == 0){

            //check to see if the file name is in the filename list
            FileData* fileItr;
            for(fileItr = itr->head_fd; fileItr!=NULL; fileItr = fileItr->next_fd){
                //if the file is already in the list
                if(strcmp(fileItr->filename, filename)==0){
                    fileItr->token_count++;
                    return;
                }      
            }
        }
    }

    //if there at this index in the hashtable, add to the hashtable and return
    if(token_table[index] == NULL){
        token_table[index] = createHashToken(token, filename);
        return;
    }

    //if the new node being added is greater than the first node
    else if(token_table[index]!=NULL && 
            compare_str(token ,token_table[index]->token)<0){
        
        HashToken* temp = token_table[index];
        token_table[index] = createHashToken(token, filename);
        token_table[index]->next = temp;
        return;
    }

    //if the token is in the hastable, but the filename isn't
    else{
        HashToken* ptr=NULL;
        
        //loop over the table to fin token
        for(ptr = token_table[index]; ptr!=NULL; ptr = ptr->next){
            
            //if the token is in the list, add the filename if different
            if(strcmp(ptr->token, token)==0){
                 
                FileData* itr = NULL;

                //loop through the files
                for(itr=ptr->head_fd; itr!=NULL; itr=itr->next_fd){
                    
                    //append the list using alphanumerics
                    if(itr->next_fd != NULL &&
                        compare_str(filename, itr->filename)>0 &&
                        compare_str(filename, itr->next_fd->filename)<0){
                        
                        //insert into the middle of the linked list
                        FileData* temp = itr->next_fd;
                        itr->next_fd = createFileData(token, filename, 1);
                        itr->next_fd->next_fd = temp;

                        //done inserting, so just return
                        return;
                    }
                    
                    //if we get to the last position, append to the end and return
                    else if(itr->next_fd == NULL){
                        itr->next_fd = createFileData(token, filename, 1);
                        return;
                    }
                }
            }             
        
            //if the token isn't in the list
            //and we are in the middle of the list based on alphabetic
            else if(ptr->next != NULL &&
                    compare_str(token, ptr->token) > 0 &&
                    compare_str(token, ptr->next->token)<0){
                
                //append to the middle 
                HashToken* temp = ptr->next;
                ptr->next = createHashToken(token, filename);
                ptr->next->next = temp;

                return;
            }

            //done check to see if new token belongs at the end,
            //just kind of hoping that if all other conditions aren't met,
            //we can just add it to the end
            else if(ptr->next == NULL){

                ptr->next = createHashToken(token, filename);
                return;
            }
        }
    }

   
    

} 

//goes through all the tokens in the token table and prints out the data
void printTokenTable(){
    //loop through alphabet
    int i = -1;
    for(i=0; i<26; i++){
        
        printf("INDEX: [%c]\n", 'a'+i);

        //loop through tokens in hashtable
        HashToken* itr = NULL;
        for(itr = token_table[i]; itr!=NULL; itr=itr->next){
            
            printf("\tToken: %s\n",itr->token);
            
            //loop through files in each token
            FileData* ptr = NULL;
            int count=0;
            FileData* sorted = sortFileData(itr->head_fd);
            for(ptr=sorted; ptr!=NULL; ptr=ptr->next_fd, count++){
                printf("\t\t%d. Filename: %s\n\t\tTokenCount: %d\n",count, ptr->filename, ptr->token_count);
            }
        }
    }
}

void listdir(const char *name, int level){
    DIR *dir;
    struct dirent *entry;

    if(!(dir = opendir(name)))
        return;
    if(!(entry = readdir(dir)))
        return;

    do{
        //if the FD is a directory, recurse
        if(entry->d_type == DT_DIR){
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            path[len] = 0;
            
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;

            //printf("%*s[%s]\n", level*2, "", entry->d_name);
            listdir(path, level + 1);
        }
        //else if it is a file
        else{
            //create full path to file to be read
            char path[1024];
            int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            path[len] = 0;
            
            //read and get it as a string
            char* fileTokens = readfile(path);

            //get all the tokens as a list and store the filename
            TokenList* tokenList = split(fileTokens, entry->d_name);

            int amount = tokenList->tok_amount;
            char* filename = tokenList->filename;

            int i;
            for(i=0; i<amount; i++){
                char* token = tokenList->unsort_tokens[i];
                addToken(token, filename);        
            }
            //printf("%*s- %s\n", level*2, "", entry->d_name);//prints for testing purposes
        }
    } while(entry = readdir(dir));
    closedir(dir);
}

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
             
            FileData* sorted = sortFileData(itr->head_fd);
            for(ptr=sorted; ptr!=NULL; ptr=ptr->next_fd, count++){
                printf("\t\t<file name=\"%s\">%d</file>\n",ptr->filename, ptr->token_count);
            }
            printf("\t</word>\n");
        }
    }

    printf("</fileIndex>");
}

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
