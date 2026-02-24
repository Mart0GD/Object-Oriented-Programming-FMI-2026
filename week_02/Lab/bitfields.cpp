#include <iostream>

// size of the struct = 4 bytes
struct compact {
    unsigned int hour    : 5; // [0,32)
    unsigned int minutes : 6; // [0,64)
    unsigned int seconds : 6; // [0,64)

    // Total used: 17 bits
    // Remaining in the 32-bit int: 15 bits (internal padding)
    // Total size: 4 bytes (Padded to be divisable by 4)
};

struct empty_space {
    unsigned char val1 : 6;
    unsigned char      : 4;
    unsigned char val2 : 5;

    // Size of first partition -> 6 + 2 (padding)
    // Size of second partition -> 4 + 5 = 9 > 8 => 2 bytes

    // Result: 1 byte + 2 bytes = 3
};

struct block_break {
    unsigned char size_three : 6;
    char size_one            : 4; // New block begins here, we wasted 5 bytes
    unsigned char            : 5;

    // Size of first partition -> 6 + 2 (padding)
    // Size of second partition -> 4 + 5 = 9 > 8 => 2 bytes

    // Result: 1 byte + 2 bytes = 3
};

int main(){
    std::cout << sizeof(empty_space);
}