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
        sprintf(alphas[i],"%.*s", interval, str + inter_tab[i][0]); //write the string to the alpha array
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
