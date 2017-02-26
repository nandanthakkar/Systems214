## Systems Programming - Lecture 1 - Computer Architecture Review

#### C Hacks:

###### <u>Struct Declaration:</u>
```C
==============================
Traditional Struct Declaration
==============================
typedef struct Thing{
	int  i = 2;
	char c = 'c';
}

/*
 *Short Hand Declaration
 *(the struct must be declared)
 */
Thing t = {2,'c'};

```

###### <u>Boolean Hack</u>
```C
=======================
Create booleans in C
=======================
typedef enum bool{false, true} bool;

bool t = true;
bool f = false;
```

###### <u>Function Pointers:</u>
```C
=======================
Function Poiter Example
=======================
void example_func(int i, char* str, struct Stuff s){
	//code here
}

//Function Pointer
void (*example_func)(int, char*, struct Stuff);
```

---

#### Difference between a Struct and a Union

###### <u>Unions</u>
A Union allocates memory for the largest data type, and morphs the data according to the data 
you are trying to store.

```C
================
Union Example
================
typedef union Example{
	int i;
	long l;
}Example;

//You only declare for one value
Example e = {10000};
```

When the initial piece of data is passed into a union, the largest data type will be the size used
to allocate memory. When interacting with data stored in the largest data type, all data 
manipulations will proceed as normal. When interacting with smaller data types, the initial data 
that is stored within the byte limit of the smaller data type is what is used as the value for
the smaller data type. This saves memory, but can cause for smaller data types to store garbage data.
 
###### <u>Structs</u>
Unlike a union, a struct allocates memory for all the data types that are given at declaration.


