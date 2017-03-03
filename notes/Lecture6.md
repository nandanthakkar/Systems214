## Systems Programming - Lecture 6

#### Dynamic Memory with Structs

##### Allocating memory

Storing data in dynamic memory requires to first `malloc` room for the data, then use `memcpy` to copy the data in.
<b>Note: `strcpy` should be used if you are trying store data in a string.</b>

```C
#include <stdlib.h>
#include <string.h>

typedef struct _Node{
	char* str;
	int * num;
	struct _Node* next;
}Node;

/*
 * malloc room for a Node
 * malloc room for the string in a node
 */
Node* create(char* string, int num){

	Node* ptr = (Node*)malloc(sizeof(node));

	ptr->next = NULL;
	
	//malloc room for the string and copy it over
	ptr -> str = (char*) malloc(sizeof(char)* strlen(string));
	strcpy(ptr->str, string);

	ptr -> num = (int*) malloc(sizeof(int));
	memcpy(ptr -> num, num);

	return ptr;	
}
```

##### memcpy vs. strcpy
1. `strcpy` copies data up until it reads a null characrer. So when reading through a stream of memory/bytes, `strcpy` will read up until a null charcter and <b>include the null character</b>.
2. `memcpy` always copies the exact number of bytes into memory. 

---

#### Freeing Memory 
When freeing data inside of a struct, <b>ensure the data of the variables inside the struct are freed</b> before freeing the reference to the struct itself.

```C
//Node used in example
typedef struct _Node{
	char* str;
	int * num;
	struct _Node* next;
}Node;

/*
 * Destroy the data in side before you the struct itself is destroyed
 * THEN destroy the struct.
 */
void destroy(Node* node){
	free(node->str);
	free(node->num);
	free(node);
}
```
