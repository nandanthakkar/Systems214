#include "modules.h"
#include <errno.h>

//main method
int main(int argc, char** argv){
 
    listdir("./test", 0);
    printTokenTable();
    
    //compare_str("this", "toast");
    return 0;

}
