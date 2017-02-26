#include <stdio.h>

int main(){

	char mychars[10];
	
	size_t* location = (size_t*)(&mychars[5]);
	*location = 22;	
	printf("%d", *(size_t*)(&mychars[5]));


	return 0;
}
