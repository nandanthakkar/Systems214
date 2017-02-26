## Systems Programming - Lecture 10

#### Process

##### What is a Process?
OS' abstraction for running code.... but how?

Lets imagine we had the set of bits: `101001001101001010110`. What do these bits mean?
The answer is that they can mean anything, it requires a program to understand what these bits mean.

While there is technically no way for us to understand what this means, we can think about the different ways to we can create different meaning ffor the same strip code. Generally speaking, the only way to infer diffferent meaning from the same set of bits is from rearraging what each subset of bits means. 

##### Running a Process
The `fork` command duplicates the calling process you run the command. 


fork-> make copy -> replace with new code -> exec (run new code) 

processes CAN NOT modify another processes memory.

Pid
Signal Position/file handles
Memory area
if(process is a child) then process also includes the `parent pid`


Can check to see if a parent process and child process are different by having different pid's. `fork` has this built in. The parent process is labeled is labeled as a number greater than 0. therefore, if `fork` returns 0 to the child process. Once the child process gets back the pid that were delievered from fork, `exec` is then run on the pid that equals 0. 


Where does `exec` actually return to?
<b>TODO:</b> FILL THIS ANSWER

Example of running a process in C
```C
int status = fork();
if(status == 0){
	exec("./program");
}
```

##### General Review
`fork()`: Called once, returns twice (once to parent once to child
`exec()`: Called, but doesn't return in normal operation
---

#### Killing Processes

##### When Should the OS Clean up a Proess?
<b> FILL IN BUBBLE,</b>

##### <i>wait</i> Command & Killing a process
When a parent process calls `wait` on a child process, only then can a child process be killed when a child process is done. If the OS trys to kill a child process and it is still running, the OS will `wait` for in, hence `wait`. tells the OS to wait for a process 

##### Zombie Process
When a chid process that has no more exectuion to do, has returned, but parent has not called wait() on it yet. 

##### Orphan Process
Child process whose parent has died without calling wait. (Yes, you can have <i>zombie orphans</i>

##### Init (Scheduler) - Process 0
A process that knows how to schedule processes to run. When this process runs, it is invoked from some easily acesible place on the harddrive which then runs the OS and schedule the rest of the processes. 

`Init` also has the ability to adopt and orphan processes and `wait`s on them

