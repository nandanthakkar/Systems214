## Lecture 3 - Systems Programmig

#### structs and typedef

The follwing is not allowed in C. `struct Node next;` must be a pointer...
```C

struct Node{
	char *token;
	struct Node next;
}
```

This version of the struct now works because `struct Node next;` is now `struct _Node* next;`, thus the compiler can now refer to a reference a Node in the heap and or on a stackframe.
<i>NOTE:</i> This struct is also but it is also applies `typedef`, which allows me to rename a type that I created

```C
typedef struct _Node{
	char* token;
	struct _Node* next;
}Node;

//because _Node is typedefed, instatiation is allowed to be as follows:
Node* n = (Node*) malloc(sizeof(Node));

//but you can also declare a struct using the original name
_Node* n = (_Node*) malloc(sizeof(_Node));

//you can alos interchange these names because Node is typedefed (aliased) to _Node
_Node* n = (Node*) malloc(sizeof(_Node));
```

--- 

#### enums 

An `enum` is just a list of constants that are backed up by integers.

<b>Example:</b> Demonstrates how to create a list of type `enum`.
```C
enum volumes {PINT, QUaRT, GaLLON}
```

<b>Example:</b> Creating a reference to an enum and running it through a conditional.
```C
enum volumes aJar = PINT;
if (ajar == PINT){//do stuff}
```

When applying `tyepdef` to an `enum` set, you can rename an `enum` set to allow the compiler to understand an `enum` set as if it was cosnidered to be a recognized type. 

<b>Example:</b>
```C
typedef enum volumes capacity;
capacity somesize = QUaRT;
```

---

#### Pointers

Pointers are a built in type in C-Language, where the only compatiable type to a pointer is a `void*` (you can think of `void*` as the most general version of data). 

###### Declaring a Pointer
Because pointers point to memory addresses, you have to have a general way to refer to the memory address of any data-type. In C-Language, we use the `&` character to refer the memory address of a type. 

<b>Example:</b> Creating a pointer to a data-type.
```C
int a = 5;
int* ptr = &a;

if(*p == 5){
	//do stuff
}
```

In general, `p ≡ &b` and `*p ≡ 5`.

###### Pointer Arithmetic

Once you are refering to a specific memory address of a given data-type, you can begin to iterate over memory quite easily.
This concept is known as <i>pointer arithmetic</i>, and it allows you to move through pieces of memory. The proper notation is as follows:
<b> Example:</b> Moving over a space in memory by the size of an integer. 
```C
int b = 5;
int *p = &b;
p+1;
```

It's worth noting that when you `+1` - or more generall `+n` to a memory address, you will increase the pointers referenced memory location by the size of the data-type the pointer is refering too. Using the previous example, adding `+1` to the memory address of `b` is really moving to the memory address `&b+sizeof(1*int)`

###### Pointer Artihmetic and Arrays

Applying <i>pointer arithmetic</i> to arrays is quite an obvious idea once you understand the concept of pointers. Because array elements are adjacent to one another in memory, adding `+1` to the memory address of an array element will simply move you to the memory address of the next array element. 

<b>Example:</b>

```C
char stuff[] = {'c','h','a','r','\0'};
char* letter = stuff;

//stuff[0] ≡  *(letter+0);
//stuff[1] ≡  *(letter+1);
//stuff[2] ≡  *(letter+2);
```

---

#### malloc

`malloc` is short for `memory allocation` and is a function that is located within the `#include <stdlib.h>` system library. Like most C standard libraries, `#include <stdlib.h>` is an OS specific library that gives you access to any given OS' memory allocation framework. Generally speaking, this library is implemented differently for each OS and system architecture. Ultimaltey, using `malloc` and several other functions provided by `#include <stdlib.h>` gives the user the ability to allocate memory within the heap. 

<b>Example:</b> Allocates memory for a single character in the heap.
```C

//creates memory for one character
char* p = (char*) malloc(sizeof(char));

//creates memory for n characters
//essentially how an array works
char* p = (char*) malloc(n * sizeof(char));
```
