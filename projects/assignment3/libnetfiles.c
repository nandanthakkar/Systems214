/*
 * Author: Douglas Rudolph & Nandan Thakkar
 * File: server.c
 * Course: Systems Programming - CS:214
 * Professor: Dr. Fransisco
 * Created: April 19th, 2017
 */

#include "libnetfiles.h"

/**
 * Purpose: The purpose of 'netwrite' should return the number of bytes actually written to the
 *          file associated with some file descriptor.
 *
 * Description: 1.) Return Value: The return value is -1 on failure.
 *              2.) The file descriptor that is being sent in should be the negative value to
 *                  the real file descriptor that is stored on the server.  
 *              
 *
 * @param: fileDescriptor: The place the data is going to be written to.
 * @param: buffer: The data that is actually being written
 * @param: nByte: The amount of data that is going to be written.
 *
 */
ssize_t netwrite(int fileDescriptor, const void* buffer, size_t nByte){
    
    //1. Check file descriptor table to see if the table exists.
    //2. If not, return -1.
    //3. If so, create the buffer and write the data.
    //4. Return the amount of data that was read.
    return -1;
}

/**
 * Purpose: The purpose of 'netread' should return the number of bytes that were written to the
 *          file associated with some file descriptor.
 *              
 *
 * Description: 1.) Return Value: The return value is -1 on failure.
 *              2.) The file descriptor that is being sent in should be the negative value to
 *                  the real file descriptor that is stored on the server.  
 *  
 * @param: fileDescriptor: The file descriptor that is going to be read.
 * @param: buffer: The place in which data is written to.
 * @param: nByte: Number of bytes.
 */
ssize_t netread(int fileDescriptor, void* buffer, size_t nByte){
    //1.) Check the file descriptor table to see if the table exists
    //2.) If not, return -1
    //3.) If so create the buffer to read the data
    //4.) returns the number of bytes actually read
    return 	-1
}
