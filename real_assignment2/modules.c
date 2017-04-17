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

    //if there are token is in the hastable, but the filename isn't
    else{
        HashToken* ptr=NULL;
        
        //loop over the table to fin token
        for(ptr = token_table[index]; ptr!=NULL; ptr = ptr->next){
            //if the token is in the list, add the file name is different
            if(strcmp(ptr->token, token)==0){
                 
                FileData* itr = NULL;

                //loop through the files
                for(itr=ptr->head_fd; itr!=NULL; itr=itr->next_fd){
                    
                    //append the the list using alphanumerics
                    if(itr->next_fd != NULL &&
                        compare_str(itr->filename, filename)>0 &&
                        compare_str(itr->next_fd->filename, filename)<0){
                        
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
        }
    }

    //if we get here, the token isn't in the hashtable
    //increment to the end of the hashtable and insert
    HashToken* ptr=NULL;
    for(ptr=token_table[index]; ptr->next!= NULL; ptr=ptr->next);
    ptr->next = createHashToken(token, filename);
    

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
            for(ptr=itr->head_fd; ptr!=NULL; ptr=ptr->next_fd, count++){
                printf("\t\t%d. Filename: %s\n\t\tTokenCount: %d\n",count, ptr->filename, ptr->token_count);
            }
        }
    }
}
