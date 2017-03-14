## Systems Programming - Lecture 5

#### malloc, calloc, realloc

Is `sizeof(struct thing)` ≥ `sizeof(char)+sizeof(int)`?

<b>Prompt Code</b>
```C
struct thing{
	char c;
	int i;
};
```

In this case where both structs and the `malloc` functin are being used, structs have the potential of taking up more memory than simply just the size of each datatype found within the struct. Because of the way `malloc` alloates memory, `malloc` simply only tries to find a gap in open memory where both data types fit, reguardless of if the program is waisting space. Thus, the size of that the program is using in memory has the potential of being more than neccessary.  


##### Difference between malloc and calloc
As described in the previous part, malloc doesn't always allocate memory to match the exact size of the entire struct, it simply just has to be relativley close in size. Another sublte piece of `malloc` that is often forgotten is that `malloc` doesn't initialize the data it allocates to be a specific value. If for some reason, you would like the data you allocate to have a set value when the memory is being allocated, `calloc` is an alternative option to `malloc`.

`calloc` is a function that allocates memory contiguously, thus the the name `Contiguous Allocation`. Another subtility to `calloc` is that `calloc` will look through memory to find a space of contiguous memory that matches the <b>exact</b> size of the data type you are tryign to allocate.

<b>calloc Example:</b>

```C
#include <string.h>

char* create_str(char* str){

	/* similar to the following line
	 * char* str = (char*)malloc(strlen(str)*sizeof(char));
	 * main difference is that calloc makes sure all the defualt information is null
	 * malloc will just grab data and not clear the memory you are allocating
	 */
	
	//create a string in memory, set the 
	char* end_str = (char*) calloc(strlen(str), sizeof(char));
	strcpy(end_str, str);
	return end_str;
}
```

##### realloc and Allocation Time

When allocating memory in C-Languge with `realloc`, one has to remember be careful about how long it takes C-Language to allocate memory. In the case of `realloc`, C-Laguage has to reach out the OS, have the OS find a new open space in memory to for the information to be copied over too, copy the information, and reassign the pointer to the new memory location. One can imagine that this process could take a while simply due to the amount of time it takes to find a new location as well as copying the old information over. Because of this, one has to be careful of calling the data in  memory the pointer is refering too <b>right after</b> calling `realloc`. Technically, This process gets handled by the OS, thus, by the time the the line of code `realloc` is located on finishes executing, several more lines of the program could have run. 

<b>Dangeous Example</b>
```C

int* p = (int*) malloc(sizeof(int)):

p = (int*) realloc(p, sizeof(int)*2);
print("%d\n", *p);

//might break because the OS doesnt ensure that memeory is allocated right after you call realloc

int* q = (int*)realloc(p, sizeof(int)*2);
print("%d\n", *q);

```

---

#### Freeing Pointers

##### Freeing a Pointer... Twice
Freeing a pointer is simply a process in which C-Language tells the operating system that the said memory location doesn't need to be tracked for the following C-Program. In the case that something is freed twie, the consequences are unpredictable. Thus, you just have to remember to <b>never</b> free something that has already been freed and is null. 

```C

typedef struct _Node{
	char c;
	int p;
}Node;

void destroy(Node* p){
	free(p);
	free(p);
}
```

##### Freeing a Pointer that is on the Stack 
When freeing pointers, it's important to remember that freeing a pointer that doesn't point to memory in the heap is completely unnecessary. Because the pointer lives on the stack, so does the data is the pointer is pointing to, thus the call-stack will handle remvoing the data from memory. 

```C
void foo(){
	int a = 5;
	int* p = &a;
	
	//unnecessary to free p
	free(p);
}
```

--- 

#### The Mess that is C-Lang. Constants

```C

/* 
 * This line can be read as: "int pointer that has a constant reference"
 * An easy way to think of it is: int (const*) p
 * So it's pointer to an integer constant
 */
int const* p; 

/*
 * This line can be read as "constant integer pointer
 * An easy way to think of it is: const (int*) p;
 */
const int* p

/*
 * 
 */
int* const p

/*
 *
 */
const int* const p

const int a = 5;
int* p = &5;
```

```C
//The char* that strlen recieves is now a constant and can manipulate the data
int strlen(const char* str){
	int i=count=0;
	for(i = 0; str[i] != NULL; i++)
	    count++;

	return count;
}

```

