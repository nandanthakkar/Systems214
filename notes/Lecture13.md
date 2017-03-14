## Systems Programming - Lecture 13

#### I/O

##### Blocking vs Non-Blocking
Blocking: Function does not return until it is done
Non-Blocking: Function return... before it is done. Ask it to do some job, and it will run that job for as long as the process will run, and then return even if the process is not done running. 

- `read` is a <u>non-blocking call</u> that returns an integer representing the amount of bytes that it actually read. 
Example: 
```C
fd ...
char* ptr = (char*) malloc(sizeof(char)*100);
int status = 0;

/**
 * FILE_DATA: hello world
 */

//read the first 4 bytes from a file
status = read(fd, ptr, 4);

//ptr = "hell"

//overwrites the data in ptr
status = read(fd, ptr, 4);
//ptr = "o wo"
```

Reading data with `read` that doesn't overwrite data
```C
//file-descriptor to "somefile"
int fd = open("./somefile",);

/*
 * FLAGS:
 * O_RDWR = open read & write
 * O_RDONLY = open read only
 * O_WRONLY = open write only
 * O_CREAT = Create a file
 */

/*
 *if you want to do multiple things when you call open, you use a bitwise or with the flags
 * open("./somfile", O_CREAT|O_RDONLY)
 */

 //open is how you create new files

int amount = 100;

//file-descriptor to "somefile 
int readin = 0;
char* ptr = (char*) malloc(sizeof(char)*amount);
int status = 0;

while(amount > 0){
	//move the offset up by the amount of characters the OS was capabale of writing. 
	offset += status;
	
	//move ptr up so we don't overwrite previous data.
	status = read(fd, ptr+offset, amount);
	
	if(status > 0){
		amount -= status;
	}
	else{
		//error handle
	}	
}

//make sure to close the file-descriptor
close(fd);
```

#### readdir  
To read a directory, we can use readdir (man 3 readdir) is essentially an iterator that returns a struct dirent that talks about a given entry in a directory (go to readdir, hand it the file descriptor, and a pointer to a directory entry will paramterize the struct fr you, will tell whether item is a file or a directory. 

opendir
readdir
- in type field, DT_DIR -> it is a directory
- in type field, DT_REG -> it is a regular standard garden variety file

- everytime we readdir, it tells us about the next thing (can't go backwords; molds it self to a linked-list.)
- everytime you readdir through everything in a directory, it will return NULL.

- when calling the filename variable within the __ struct, the variable only stores JUST the filename, not the path leading up to the filename

#### lseek

```C
int file = lseek(fd, 0, SEEK_END);
lseek(fd, -filelength, SEEK_CUR);

