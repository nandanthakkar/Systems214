## Systems Programming - Lecture 2 - Computer Architecture Review

#### C Headers

###### stdio
```C
#include <stdio.h>
```

The I/O functionality of C is fairly low-level by modern standards; C abstracts all file operations into operations on streams of bytes, which may be "input streams" or "output streams". Unlike some earlier programming languages, C has no direct support for random-access data files; to read from a record in the middle of a file, the programmer must create a stream, seek to the middle of the file, and then read bytes in sequence from the stream.

------

###### stdlib
```C
#include <stdlib.h>
```

The C standard library provides macros, type definitions and functions for tasks such as string handling, mathematical computations, input/output processing, memory management, and several other operating system services.

------

###### unistd
```C
#include <unistd.h>
```

Is the name of the header file that provides access to the POSIX operating system API. It is defined by the POSIX.1 standard, the base of the Single Unix Specification, and should therefore be available in any conforming (or quasi-conforming) operating system/compiler (all official versions of UNIX, including Mac OS X, Linux, etc.).

---

#### Arrays

###### Declaring an Array 
```C
int array[10];
```

###### Initialization List
```C
int array[] = {1,2,3,4};
```

###### Limited Initialization List
```C
int array[3] = {1,2,3};
```

---

#### Arrays as Strings

###### Example of a String as an Array 
```C
===========================
same as a char* type string
===========================
char array[] = {'h','e','l','l','o','\0'}
print("%s",array);

//output = hello
  
```

---

#### Weird C Subtilities 

###### Forgetting the new-line character can cause several issues:
1. If there is a zero in memory right after the string, it will stop printing the string just as if there was a newline.
2. If there is a no zero following the string, it could potentially print garbage data up to the first zero.
3. It might print entirely garbage data and will continuely print it in the rare case there is no 0 in memory.

###### What happens if you try to print a string as a digit?
The string's memory address will be printed
```C
char* str = "Hello, cruel world!";
printf("%d",str);
```

###### Pointers with Arrays
There are two ways of setting a pointer to an array. The first is to set a pointer to point to the memory address of the leading element.
The other way is to set a pointer equal to the array itself. In the second option, setting the pointer to the array itself is setting the pointer to look at the memory address of the array, which so happens to be the memory address of the first element.

<b>Example:</b> Pointing a `char*` to the beginning of the array.

```C
char* ptr = &arr[0];
```

<b>Example:</b> Pointing a `char*` to an array <b>also</b> points to the memory address of the first element.
```C
char* ptr = arr;
```

---

#### Data & Pointer Arthimetic

###### Pointer Arithmetic 
Adding one to a pointer moves the the pointer over in memory by the size of the pointer data-type

```C
int array[] = {1,2,3,4,5};
int* ptr = array[0];

==================
output = 1
==================
printf("%d",*ptr);


==================
output = 2
==================
ptr += 1;
printf("%d",*ptr);

```

###### sizeof
Tells you the `sizeof` a data-type

```C
printf("%d", sizeof(int));
printf("%d", sizeof(char));
printf("%d", sizeof(double));
printf("%d", sizeof(long));

```

###### Data-types
1. chars are always 1 byte
2. `short` ≤ `int` ≤ `long`

Data-types (besides `char`) have different sizes on differet machines, thus C compilers will have to make the sizes of 
`int`'s, `double`'s, `long`'s, etc. relative to one another.
