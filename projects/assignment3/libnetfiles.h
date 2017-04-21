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
#include <unistd.h>

//TYPES

//create boolean types
typedef enum _bool{false=0, true=1} bool;





//FUNCTIONS

//writes to server
ssize_t netwrite(int fileDescriptor, const void* buffer, size_t nByte);

//reads to server
ssize_t netread(int fileDescriptor, void* buffer, size_t nByte);
