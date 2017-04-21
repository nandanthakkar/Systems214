/*
 * Author: Douglas Rudolph & Nandan Thakkar
 * File: server.c
 * Course: Systems Programming - CS:214
 * Professor: Dr. Fransisco
 * Created: April 19th, 2017
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>

/**
 * Purpose: The function that is constantly listening for a connection on the main thread
 *
 * Description: 1.)
 *              2.)
 *              3.)
 *
 * @param: void: No incoming parameters 
 */
int main(void){
	
    /*
     * THIS CODE IS EXAMPLE CODE TO RUN AN ECHO SERVER
     * Description: not much needs to be changed other than moving the buffer to another thread
     */
	char str[100];
    int listen_fd, comm_fd;
 
    //socket connection that is going to be made from the server
    struct sockaddr_in servaddr;
    
    //create a socket using the Address Family
    listen_fd = socket(AF_INET, SOCK_STREAM, 0);
 
    //places n zeroed value bytes in the memory address of the server address
    bzero( &servaddr, sizeof(servaddr));
 
    //1.) Make the server address of type address family - (AF_INET)
    //2.) Convert the data that was written as 'host' byte integers to 'network' byte integers 
    //    - Basically allows the server to read the data correctly after being sent of the network
    //3.) Establish a connection through the socket on port 22000 (this port will change)
    servaddr.sin_family = AF_INET;                  //1.)
    servaddr.sin_addr.s_addr = htons(INADDR_ANY);   //2.)
    servaddr.sin_port = htons(22000);               //3.)
    
    //Bind the connection with the socket
    bind(listen_fd, (struct sockaddr *) &servaddr, sizeof(servaddr));
 
    //Listen on this socket for up to 10 established connections
    listen(listen_fd, 10);
    
    //accept the connection
    comm_fd = accept(listen_fd, (struct sockaddr*) NULL, NULL);
 
    //Run until the server crashes or until we are done listening
    while(1)
    {
        //zero out data for a buffer up to 100 bytes (A.K.A.: 100 characters)
        bzero(str, 100);
        
        //read data over socket
        read(comm_fd,str,100);
 
        //instead of printf, send data to another thread, and listen on that thread
        printf("Echoing back - %s",str);
 
        //write data 
        write(comm_fd, str, strlen(str)+1);
 
    }
}




