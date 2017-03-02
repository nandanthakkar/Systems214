## System Programming - Lecture 4

#### Arrays and Pointers (continued)

Creating arrays in C is essentlially creating a single pointer that is pointing to a list of a sepcific data type.

`arr[2]` ≡ `*(&arr[0]+2)` ≡ `*(arr+2)`

```C
int arr[] = {1,2,3,4,5,6,7,8,9,10};

========================
Arrays utilize pointers
========================

printf("%d",arr[1]);
printf("%d",*(arr+1));

//the output for both of these statemenets are 2`
```

---

#### Escape Sequences & Printing Data

##### Escape Sequences
- `\n` - new line character
- `\t` - tab character
- `\"` - prints the `"` character
- `\v` - vertical tab character
- `\b` - backspace character

##### Printing Datatypes
- `%d` or `%i` - Prints integers
- `%x` or `%p` - Prints Hexadecimal
- `%ul` - Prints unsigned longs
- `%s` - Prints strings
- `%f` - Prints floats

---

#### Memory & Malloc

When declaring variables, a variable will contain garbage data in it if you do not initialize it. 
By default you should <b>always</b> initialize variables when you create it.

```C
//don't do this
int i;

//do this
int i = 0;
```

#### 
When returning pointers, you have to be careful to not pass around pointers that aren't pointing to `malloc`ed data. 
If you return data that isn't `malloc`ed data, the data you are trying to get from the function call is gone due to the stackframe being deleted.

```C
int* func(int b){
	int c = 100;
	int *p = &c;

	return p;
}

int* q = func(5);
```

Proper way to return variables.  

```C
int* func(int b){
	int c = b+1;
	int* p = (int*) malloc(size(int));
	
	//set the data of p equal to the data within c.
	*p = c;
}
```
