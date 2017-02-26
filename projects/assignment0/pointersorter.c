/* AUTHOR: Douglas Rudolph
 * FILE: pointersorter.c
 * DUE DATE: Feb 5, 2017
 * PROF: Dr. Francisco
 * COURSE: Systems Programming - Assignment 0
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*
 * STRUCT: Node
 * PURPOSE: Used for chainging together a linked list of storted strings
 */
typedef struct _Node{
	char* str; 
	struct _Node* next;
}Node;

/*
 * FUNCTION create_node
 * PURPOSE: used to create a node that takes requires a char* that is allocated
 */
Node* create_node(char* string){
	//allocate memory for a node with a defualt value
	Node* node = (Node*)calloc(1, sizeof(Node));	
	
	//set the next Node in the list to be NULL by default
	//this is uesful for when you are looping through the list until the loop hits NULL
	node->next = NULL;	
	
	//allocate memory & point node->str at the string we want to copy into said Node
	node->str = strdup(string);
	return node;	
}

/*
 * FUNCTION: insert
 * PURPOSE: used to insert a Node into a list with the intention of a node 
 * 		    going into it's sorted position.
 */
Node* insert(Node* root, char* str){
	
	//if the root Node  is NULL, add a new string to the front of the list, 
	//then return the updated root Node.
	if(root == NULL)
	{
		root = create_node(str);
		return root;
	}

	//if a new Node's sorted position is before the root Node
	//update the root node and push all elements of the list down 1 position.
	else if(strcmp(root->str, str)>0){
		Node* temp = root;
		Node* new_root = create_node(str);
		root = new_root;
		root->next = temp;
		return root;
	}
	
	//if the first two statements were not triggered, 
	//a new Node has to added somewhere after the root Node.
	else{

		//loop through until a position in the list is found such that
		//it belongs in the center of the list, but not the end
		Node* ptr = NULL;
		for(ptr = root; ptr->next != NULL; ptr = ptr ->next){
			
			//check to see if the node we currently at is less than the char* we want to add,
			//but the one immediately following is greater.
			if(strcmp(ptr->str, str)<0 && strcmp(ptr->next->str, str)>=0){
				Node* temp = ptr->next;
				ptr->next = create_node(str);
				ptr->next->next = temp;
				return root;
			}
		}


		//if we get to the end of the list, then this new Node belonds at the end of the list.
		//this is because the condition in the for-loop stops at the last element, 
		//and bypassed all other possible race conditions.
		ptr->next = create_node(str);
		return root;
	}
	
	
}

/*
 * FUNCTION: print_list
 * PURPOSE: To Run through the sorted linked list and print all elements out one-by-one
 */
void print_list(Node* root){
	
	//create a ptr, set to NULL by default
	Node* ptr = NULL;
	
	//loop through while ptr isn't at the end of the list
	for(ptr = root; ptr!=NULL; ptr = ptr->next){

		//print string ptr is referencing
		printf("%s\n", ptr->str);
	}
}

/*
 * FUNCTION: destroy
 * PURPOSE: loop through the list and destroy it
 */
void destroy(Node* root){
	//reference to root
	Node* ptr = root;

	//run until there are no more pointers
	while(ptr != NULL){
		
		//make temp pointer to everything past ptr
		Node* temp = ptr->next;
		
		//free the char* the current Node as well as the Node itself
		free(ptr->str);
		free(ptr);
		
		//move the ptr to the next element in the list
		ptr = temp;
	}

}

/*
 * FUNCTION: main
 * Purpose: Runner to the general algorithm
 */
int main(int argc, char** argv){

	//if no string is entered, return
	if(argc == 1){
		return 0;
	}

	//if there are too many strings, print usage string and return 
	if(argc > 2){	
		printf("Too many strings were entered, quting program. \n");
		return 0;
	}
	
	//create a for the root node, and set it equal to null by default
	Node* root = NULL;

	int j;

	//loop through each string that is in char** argv
	for(j=0; j<strlen(argv[1]); j++){

		//if the char currently being looked at isn't in the alphabet, replace it with a space char.
		//this filters out all possible characters and makes spaces a delimeter
		if(!isalpha(argv[1][j]))
			argv[1][j]=' ';
	}
	
	//use string tokenizer to loop through on all spaces as a deliemeter.
	char* token = strtok(argv[1], " "); 
		
	//while there are tokens, loop through them all and add it to the list.
	while(token != NULL) {		
			
		//insert token into the sorted position
		root = insert(root, token);
			
		//get the next token
		token = strtok(NULL, " ");
	}
	
	
	//print the sorted list
	print_list(root);
	
	//destroy the list
	destroy(root);

	return 0;
}
