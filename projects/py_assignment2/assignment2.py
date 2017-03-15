#!/bin/python3
"""
AUTHOR:  Douglas Rudolph
COURSE:  Systems Programming
PURPOSE: Assignment 2 prototype that shows the logic of a working 
         version of our C-Language based version of Assignment 2.
"""

#import OS python library and REGEX python library
import os, re

'''
HASHTABLE: 
    Token will be the key, the value stored will be 
    the file as well as the token count for each file.

GENERAL EXAMPLE: 
    Token -> [(file1, token_count), (file2, token_count)... (fileN, token_count)]

CONCRETE EXAMPLE: (Example from the Assignment2.pdf)
    "name" -> [("boo", 2), ("baa", 1)]
'''
tok_table = {}

#walks through a folder and reads each textfile
def stroll_file_system(rootdir):
    for root, dirs, files in os.walk(rootdir):
        
        #for files in directory
        for file in files:

            #generates the full path to the file
            #Example Path: ./example_data/adir/boo.txt
            fullpath = os.path.join(root, file) 
            
            #if a text file, read text file
            if file.endswith(".txt"):
                read_file(fullpath)

#Reads a file for distinct tokens, and organizes the data in a hashtable
def read_file(filename):
    
    #open file stream
    f = open(filename)

    #read through the file line by line
    for line in f:
        
        #make the line all lowercase, 
        #split the line by the space character and newline character,
        #and filter out any empty strings after splitting
        word_arr = list(filter(lambda x: x != '' ,re.split("[ ]|[\n]", line.lower())))
        #print(filename.split("/")[-1]+" = "+str(word_arr))

        #loop through the line word by word
        for word in word_arr:

            #check to see if the word is already a token added to the keyset
            if word in tok_table.keys():
                
                #keeps track of if the file was found in the hash table
                was_found = False

                #if so, then check to see if there exists a hash for file we are querying
                for i in tok_table[word]:
                    
                    #if the file is already in the hashtable, increase the count for THAT keyword for THAT file 
                    if i[0] == filename.split("/")[-1]:
                         i[1] += 1
                         was_found = True
                         break
                
                #else, create a hash for the current keyword with the filename
                if was_found == False:
                        tok_table[word].append([filename.split("/")[-1], 1] )

            #else, create a hash for the new keyword with the filename
            else:
                #create a list where tokens can be added to
                tok_table[word] = []
                #append a tuple where the first element is the filename, the second element is the word count
                tok_table[word].append( [filename.split("/")[-1], 1] ) 
                

#SAME THING AS MAIN METHOD
if __name__ == "__main__": 

    #run program
    stroll_file_system("./example_data/")    
    
    #print general formatted example for all output
    print("\nToken\t\t-->\t[Filename, Token_count]\n")
    
    #loop through hashtable keys, and print formattted file mappings 
    for i in sorted(tok_table.keys()):
        print("'"+i+"'"+"\t\t-->\t"+str(tok_table[i])) 
            


