## Systems Programming - Lecture 7

#### Things malloc & free do badly

##### Freeing Twice
```C
void foo(){
	int* ptr = (int*) malloc(sizeof(int));
	memcpy(ptr, 10, sizeof(int));

	//do stuff 
	
	//BUT DON'T FREE TWICE
	free(ptr);
	free(ptr);
}
```

##### Freeing something not malloced
```C
int a = 10;
int *ptr = &a;

//DON'T DO THIS
free(ptr);
```

---

#### Coding Hygeine 

##### Good Practice
1. Free everything you malloc
<b>Always initialize a to a default value.</b>
```C
//give something a default value to ensure that 
//you don't accidenly read garbage data
int a =-99

//the same can be done
int* ptr = (int*) calloc(0,sizeof(int));
```

3. Always have a return variable or staus

##### Bad Practice
1. Using representation directly
	
---

### What happens when you compile

1. Parses Definitions
2. Compile Source
3. Links code with .0 files and links .o files pre-compiled libraries

#### Macros
Macros are a way of predefining information about code before compilation. When the preprocessor, 
goes in to replace the variables, it literally just does text replacement. 

```C
#ifndef MYHEADER

#define MYHEADER
#define NUM_CORE_MACHINES 5

#endfi
```


Using macros that replace code is often a bad itea because the preprocesor doesn't check against memory,


```C
#define EXISTS !=0

#endfi

int main(){

	int a=10;
	if(a EXISTS){
		//do stuff
	}

}
```

```C
#ifndef
#define SQUARE(x) x^x
#endfi

int main(){

	int a =3;
	int b = SQUARE(a+1);
	
	//not the correct 
	int b = a+1 * a+1;

}

```
