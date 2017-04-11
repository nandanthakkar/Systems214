## Systems Programming - Lecture 19

#### Side Note for the current Assignment 3
The example code given in class was taken directly from TutorialsPoint.com

#### Detailed Overview of Assignment 3

##### Basic Order of Operations
1. We must call `netServerInit` to build a socket to set up an library related preconditions. We do incase we can't build a connection. (The server has to create a socket, open a connection, listen and bind the connectiong). We can then just refer to the server as a file descriptor once the connection is made.
2. `netopen("./", O_RDWR)` will send a message to the server, with a set of flags that user decided to send up. A message could look like such: `"14 open ./ O_RDWR"`. The number in the front is  a clever way for a server to know how long the message is in characters (ie. bytes). The rest of the message is then attempted to be run by the iLab, and if it can not run, it returns `errorno`.
3. Meanwhile on the sever side, we are going to need a table to keep track of the local file descriptors the client file descriptor is referring within the server, to which we can then just read and write data a set amount of bytes from the file descriptor that was mapped within the server. 

##### Project Extensions
1. Your file server should use multiple kernel threads. The way this is achieved is by creating an inifinite while loop that runs the `accept` function every iteration to establish an connection between the server and some arbitrary client. After that, we create a `pthread`, speicically a kernel thread so the server's OS manages how long the server will listen to the user, rather than writing our own scheduler to manange the timing system. Once the thread is created, we give that thread the `netSocketFd`. 
2. Use TCP to make the communication, but it's important to set the `TCP_NODELAY` so that TCP doesn't queue information before sending, rather we want TCP to immediately to send data. Another flag to ser it  `SO_REUSEADDR`, which allows us to reuse the port during testing. This occurs because the OS knows that the port was being used to read information for TCP, thus not allowing us to use the port number until the OS gets around to clearing that process the port was using. The `SO_REUSEADDR` flag which allows us to reuse the same address every time we open and close a server. 


