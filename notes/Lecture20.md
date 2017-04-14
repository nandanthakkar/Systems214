## Systems Programming - Lecture 20

#### Dealing with Sockets
Deal with sockets with care, use, and feeding???? 

#### Tips for Networking in C
1. Use flat data types. This means to not use `pointers`, `structs`, and `arrays. 
2. Include message length as part of/before the message.
3. Write the amount of bytes that are going to need to be read in the beginning of the `char\*` so that after the data is sent, it can be read correctly.
4. Come up with a deliemeter such that we can split up the number representing how many bytes were passed over the network, and what is actual data.

#### Handling threads with Sockets
Reading status values from pthreads to see if they returned. On the server side, we create a linked list, loop over it, and see it and see if any of the threads have finished; if so, call pthread exit. 




