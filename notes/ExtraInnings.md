## Systems Progamming - Extra Innings

#### Header Files
Header files are good for managing all the book keeping related to variables, struct definitions, enum defitions, etc. 

##### define
`#define` is a form of preprocessing and very literal runs a function that is equivalent to find and replace in a C file that `#include`s said header file.

```C
#define N 5000

int main(){
	
	int i;

	//replace N with 5000 before compilation
	for(i=0; i<N; i++){
		// do stuff
	}
}


```

##### ifndef
`#ifndef` stands for `if not defined`. `#ifndef` can be used to ensure that no header file is already imported. Every `#ifndef` must be closed with an `#endif`.

```C
#ifndef "HEADER.h"
#endif
```

##### Macros
Macros are another part of preprocessing and allow for more complex forms of the find and replace features that were descibed eariler. 

```C
//Macros can be bounded to physical sections of code
#define EXISTS !=0

//Macros can also take in parameters
#define STUFF(x) x+2
```

Be warned, using this can be dangerous, 
<b>Bad Example</b>:
```C
#define SQUARE(X) x*x

int main(){

	int a = 1;
	
	//returns 100
	printf("%d", SQUARE(10));

	/* Gets compiled down to:
	 * (a+10 * a+10)
	 * (1+10 * 1+10)
	 * (1+10+10)
	 * (21)
	 */
	printf("%d", SQUARE(a+10));

	return 0;
}
```

<b>Good Example</b>

```C
#define SQUARE(x) (x)*(x)

int main(){

	int a = 1;
	
	//still returns 100
	printf("%d", SQUARE(10));

	/* Gets compiled down to:
	 * ((a+10) * (a+10))
	 * ((1+10) * (1+10))
	 * (11*11)
	 * (121)
	 */
	printf("%d", SQUARE(a+10));

	return 0;
}
```

##### -c Compiling Flag
`-c` is a flag that allows you to compile a C file and generate the object files (`.o` files) that corespond to said `.c` file. The object files that are generated can then be linked when another `.c` file is compiled. 

Set of commands: 
1. `gcc -c some_c_file.c`
2. `gcc rsome_c_file.o runner.c`
3. `./a.out`

---

#### make
Make is a GNU unitlity that allows you to maintain groups of programs.

##### Running the make Command
Running `make` in a directory allows will look for a file called `makefile` or `Makefile`. 

##### Makefile Skeleton
1. First is the directive: depn0, ... , depnN
2. command-1 ... 
3. command-N

When looking through this general skeleton, `make` first looks at the directive and sees if all dependencies exist. If they do, `make` then runs the following commands on said depenedencies. 

##### Defualt Directives
<b>Defualt Derictive</b>: `make all` and or `make` runs on everything. 

```Make
all: test.c 
	gcc test.c

```

##### Example Makefile

```Make
#checks to make sure that test.c and thing.o exist
all: test.c thing.o

#if so, run this gcc command
	gcc: thing.o test.c
```

##### Cleaning
Clean is a part of a makefile that consists of a set of commands that may be run on complition of a program. 

<b>Example</b>:
```Make
all: test.c thing.o
	gcc thing.o test.c

thing.o: thing.c thing.h
	gcc -c thing.o

clean:
	rm *.o; rm a.out
```


