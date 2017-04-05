## Systems Programming - Lecture 18

#### Review of Threads

When creating a thread, it's important to remember that the parameters you must send into a function must be sent in as a struct. Also, it's important to remember that the `pthread_create` function takes in a `void**`. So when sending in the struct as a `void**`, we must cast the struct to a `void**` so that the thread could then read the data as a generic data-type.

Also, it's worth noting that the struct instance that we pass into the `pthread_create` function must be `malloced`. The reason why is because we are sending a handle to the pthread library, to which is a different context of the current program we are creating the thread in. Thus, we have to malloc the struct we are sending in so that the thread that is recieving the struct can reference the data that is on the current stack frame within the main thread on the program. 

```C
//Creating a thread example

```

#### Default Thread Behavior

Threads by defualt are joinable, meaning that threads that are finished can be merged. But in some cases we want threads that can't be merged. An example of this is when we create a separate thread for the GUI. The GUI thread is running for the entire life-time of the program, and usually are merged in with the main thread as one of the final cleaning calls within a program. 

#### Kernel Threads VS User Threads
<b>Kernel Threads:</b>: Extra time and space are required to construct and switch between them because the OS requires a context switch between each update of a thread. In general, Kernel scheudlers are usually pretty good - in contrast to the buggy user thread schedulers that are created in higher level applications. Also, Kernel Threads are visible by the entire system.

<b>User Threads</b>: User threads are responsible for suballocating its time over all threads. This is because user threads are handled by the process that is created from running our own program - independent from the OS. Thus, the OS doesn't handle the lifetime of user level threads. Also, User threads are very fast because we don't need to context switch, we just need to load up a different part of our code. User Threads calls on most systems are really Kernel Threads, but traditionally, User Threads are local to that process. 

If you block a process, you are clogging the entire system because the OS is only giving you alotted time to run between each thread. This ultimately means that we don't have true concurrency at the user level. The OS technically has real Concurrent abailities assuming the machine you are running the OS on has multiple cores. Only Kernel Threads have access to the threads that are on each processor of the machine. 

Now, which type of thread is more useful? The answer is that it is subjective. The type of thread depends on the type of job. In general, User Threads are becoming less and less useful and are being replaced by Kernel Threads - mainly because Kernel Threads are becoming less expensive to manage by modern day systems, making User Threads less practical. An example of this can be seen when we create a User Thread on the iLabs. The ability to create a User Thread is only available on modern systems because of backwards compatiablitiy.

#### File Descriptor Review and Ports

open("./a/file.txt") -> if continues we get a file descriptor that represents as a reference to the file made by the operating system. 
read
write
close 

What if we want to talk to a resource on another machine?
We can use IP address to reference a remote machine.
We also need a port. A port is an interface between a computer and an internal and external device. External ports are used to connect to devices like modems and printers, while internal ports are used to connect to hardware like Harddrives as well as Memory.

When we want to talk to a program (ie. a process) on another machine, we want to refer to the port number that program is running on. Thus, connecting to another machine is simply just connecting to the ip of a machine and then listening to a specific port from that machine. The process of reading and writing data to a external machine requires getting the file from the `IP:PORT` as a file descriptor, and then being able to write to the file descriptor. 

#### The Full Process of Connecting to Machine
1. Get's the IP address and convert it into a `struct host ent` with `gethostbyname`
2. Get the Port # and convert it to an int with `atoi`
3. Construct a blank `socket(AF_INET, SOCK_STREAM, 0)`
4. Build a `sockaddr_in`, initialize it, copy the representation of the IP from the `struct host_ent` into the `sockaddr_in`
5. Copy the bytes that represent the server's IP address in to the ServerIPAddress struct into our ServerIPAddressInfo struct 
6. 
