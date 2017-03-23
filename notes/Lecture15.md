## Systems Programming - Lecture 15

#### File System Jargon
1. `stat`: Command that will display file or file system status
2. <u>inode</u>: inode is a data structure on a filesystem on Linux and other Unix-like operating systems that stores all the information about a file except its name and its actual data.  
3. <u>pnode</u>:..........

#### Threads
Threads: A way to run another process in the background.
Applications: Really good for IO. Often times this is seen in GUI applications running a main thread for the user so it appears there is no lag, meanwhile the applications is auto-saving data on a timer within another thread so that the data isn't lost.

```C
int main(){
    
    do something
    //.....
    get result of something
}
```  

- Threads give themselves their stack to run within their own process space (ie. threads share the same process when running)
- To create a thread, you can call on the C pthread Library.

#### pthreads Library


##### creating an instance of a pthread
`void* arg`: an arugment that the pthread_create function that allows for you to pass in struct where each element within the struct act as arguments for  the function call you want to run on another thread.
```C
int main(){

    pthread_create(HAVE TO ADD ARGS);

}
```


##### Returning from a thread
```C

int main(){

    //do stuff

    //do this:
    pthread_exit();

    //not this:
    //exit() or _exit();
}

```

#### Signals
Like system calls, signal calls cause a context switch, the OS then takes over and pushes a new stack frame on your stack, updates the PC and stores the previous PC.

Signals are a type of interupt that presidence override all other processes that are executing. Building off of threads, calling `exit` within a thread, the thread calls a signal which performs some clean up and causes closes the thread. If `_exit()` is called, the OS stops the process immediately and doesn't clean up anything from when the process was running. 

#### pthread_join
if main returns, the threads that were part of the main thread also leave. In order to ensure that all other threads end, `pthread_join(thread, &threadStatus1)` will stop the current thread, then ensure that the other thread finishes, to which then jumps back to the original thread and finishes running.

It's worth noting that it's standard practice to join all threads, unless a thread is set to be detatched. A detatched thread is a thread that is set to never be joined back into the main thread. An example of this is a GUI, where we don't want to merge the GUI thread back into the main thread. The goal of a GUI thread is to read in input from the user and pass that data to the background thread. 
