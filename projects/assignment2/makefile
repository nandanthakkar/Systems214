default:
	gcc -g -c modules.c
	gcc -g -c file_io.c file_hashtable.c token_hashtable.c
	gcc -g -o invert modules.o file_io.o file_hashtable.o token_hashtable.o driver.c

clean: 
	rm invert
	rm -rf *.o 

