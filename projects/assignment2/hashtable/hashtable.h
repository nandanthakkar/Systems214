/*
 * AUTHOR:    Douglas Rudolph
 * FILE:      HashTable.h
 * COURSE:    Systems Programming 214
 * PROFESSOR: Dr. Fransisco
 */

//If libraries are not included, include them
#ifndef DIRS
#include <stdio.h>
#include <stdlib.h>
#include "../runner.h"
#endif

//put elements in the hashtable based on the token as the given key
void put(char* key, HashNode node);

//add key to the list
void addkey(char* key);

//used to generate the hashing location for a given key
int generate_hash();

//resets the size of the hashtable
void rehash();

//go through a delete all the objects in the table
void destroy_table();
