#!/doug/bin/python
import os
import re

#Class to store filename and word count (would be struct in C-Language)
class HashData:
    def __init__(self, filename, wordcount):
        self.filename = filename
        self.wordcount = wordcount
    def print_hash(self):
        real_filename = re.split("[/]|[.]", self.filename)
        print(real_filename[len(real_filename)-2], self.wordcount)


#words to search that were given by Fransisco's example
search_words = ['a', 'baa', 'boo', 'cat', 'dog', 'name']

indexer_hash = {}

#function to recurse through a file system and find all text files
def find_files():
    #rootdir is the directory the program starts looping through to look for text files
    rootdir = os.getcwd()+"/example_data"

    #iterate over all sub directories
    for subdir, dirs, files in os.walk(os.getcwd()+"/example_data"):
        for filename in files:
            
            #print os.path.join(subdir, file)
            filepath = subdir + os.sep + filename
            
            #if file is a textfile, count all search words inside the file
            if filepath.endswith(".txt"):
                count_search_words(filepath)

#counts the amount of times a search word is in a file
def count_search_words(filename):
    for word in search_words:
        indexer_hash[word] = []
        total = 0    
        with open(filename) as f:
            for line in f:
                finded = line.find(word)
                if finded != -1 and finded != 0:
                    total += 1
        if total > 0:
          data = [filename, total]
          indexer_hash[word].append(data)


if __name__ == "__main__":
    find_files()
    
    for i in indexer_hash.keys():
        print(i, indexer_hash[i])


