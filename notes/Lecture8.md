## Systems Programming - Lecture 8

#### Building errors

##### errno 
```C

//gives you acces to system wide error messages
#include <errno.h>

printf("%d \n", errno);
```

##### perror & sterror
What perror will do is take the error code and print out the warning that error code corresponds to. 
```C
#include <stdio.h>
#include <errno.h>

int main(){
	//print the error message
	perror(errno);

	//returns the string that corresponds with said error code
	char* error_str = strerror(errorno)
	
	return 0;
}
```

---

#### Function pointers

##### Underlying Truth about Functions
When calling a a function, or the reference to a function, we are really ineracting with some memory address -
Functions are just some memory address where a set of instructions begin.

```C

int main(){
	// foo exists at some address a, and the code in foo will run jumping to said address
	int x = foo();
	
	return 0;
}

int foo(){
	//do stuff
}

```

##### Function pointers
Because functions are just an address that indicate the beginning point for a set of instructions, 
we can make reference to said address. 

```C
float foo(int a, char b){
	//do stuff
}

int main(){

	//creates a function pointer type
	float (*func_ptr)(int, char) = foo;	

	//call the function
	printf("%d\n", func_ptr(5,'c'));

	return 0;
}
```

---
####

##### sprintf
`sprintf` allows you to print to a string, in otherwords, you can create a preformatted piece of text, and then print (write) the information to a string.

```C
#include <stdio.h>

int main(){
	char* p = "some string";
	sprintf(p, "%d, %c, %X\n",a,a,a);
}
```

##### scanf
`scanf` reads a single line of input from the standard input stream.

```C
#include <stdio.h>

int main(){
	//variable we are going to write to
	int a;

	//read information and write it the memory address of a
	scanf(&a);

	return 0;
}

```

---

#### File Descriptors
`stdin` and `stdout` are considered `file descriptors`. A `file discriptor` is an abstract indicator (handle) used to access a file or other input/output resource, such as a pipe or network socket. `File descriptors` form part of the POSIX application programming interface.

##### Writing a file descriptor
```C
#include <stdio.h>

int main(){
	
	//writing to stdin file descriptor
	fprintf(stdin, "%d, %c, %X\n", a,a,a);

	//writing to stdout file descriptor
	fprintf(stdout, "%d, %c, %X\n",a,a,a);

	return 0;
}
```


