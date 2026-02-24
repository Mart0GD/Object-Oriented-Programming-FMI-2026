#include <string.h>
#include <iostream>

// the size of package is 32 bytes
union package
{
    char str[32];
    int number;
    float real_number;
}; 

int main(void){

    package pack;

    // we have set the value of str to pesho
    strcpy(pack.str, "pesho");

    // pack.number = 1; // this is undefined, we write to already (potentially) written memory.
    std::cout << pack.str;
    return 0;
}