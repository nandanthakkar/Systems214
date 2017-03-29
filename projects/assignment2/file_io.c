#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "project.h"

char** split(char* str);

    int main(){
        char* str = "hi, my name is what? my name is, who?, my name is **WIKIKI slim shady!"; 
        split(str);
        return 0;
    }

    /*
     * Purpose: 1. Return a 2D-array of strings that are in the set of Alphanumeric strings.
     *          - Alphanumeric is defined as a string that is made of characters and numbers
     *            that MUST START with a alphabetic character.
     * 
     * Params: str: The string that will be read
     *
     * Return Type: char**: The array of alphanumeric strings
     *
     * Example: "hello, $my*name 1s albert." => "['hello', 'my', 'name', 's', 'albert']"
     */
char** split(char* str){
        
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
        //find the end of the word
        else if(inword && !isalpha(str[i]) && !isdigit(str[i])){
            inter_tab[word_count][1] = i;   // mark the closing char-pos to the word
            word_count++;                   // increase the word count by 1
            inword = false;                 // mark that we are no longer in a word
        }

        else if(inword && str[i+1] == '\0'){
            inter_tab[word_count][1] = i+1;   // mark the closing char-pos to the word
            word_count++;                   // increase the word count by 1
            inword = false;                 // mark that we are no longer in a word
        }
    }
    
    //make the array of strings
    i=-1;
    char** alphas = (char**) malloc(sizeof(word_count)); //create a 2D of strings 
    
    //loop through the indicies found
    for(i=0; i<word_count; i++){
        int interval = inter_tab[i][1]-inter_tab[i][0]; // get the size of the interval
        alphas[i] = (char*)malloc(sizeof(interval+1));  //malloc the room for the string plus character for the null char
        sprintf(alphas[i],"(%.*s)", interval, str + inter_tab[i][0]); //write the string the alpha array
        printf("%s\n",alphas[i]); //print it for testing purposes
    }

    return alphas; //return the 2d array
}

