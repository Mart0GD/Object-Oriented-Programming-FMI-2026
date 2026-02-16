#include <new>
#include <iostream>

int main()
{
    // --- Allocating a number ---
    int* number = new(std::nothrow) int(10);
    if(!number)
    {   
        // this is the error channel. The cerr channel has no buffer so everything 
        // you write is outputed immediately 
        std::cerr << "No memmory!";
        return -1;
    }

    // --- Allocating a string ---
    char* arr = new(std::nothrow) char[10];
    if(!arr)
    {
        delete number;
        std::cerr << "No memmory!";
        return -1;
    } 

    // --- Allocating a matirx ---
    char** matrix = new(std::nothrow) char * [10];
    if(!matrix)
    {
        delete number;
        delete[] arr;
        std::cerr << "No memmory!";
        return -1;
    }

    for(int i = 0; i < 10; ++i)
    {
        matrix[i] = new(std::nothrow) char[10];
        if(!matrix[i])
        {
            for(int j = 0; j < i; ++j) delete matrix[j];
            delete[] matrix;
            delete[] arr;
            delete number;
        }
    }

    // IMPORTANT!!!
    // We cannot reallocate in directly a block of memory like in C. 
    // In order to reallocate we have to allocate a new block of memory and copy the data

    for(int j = 0; j < 10; ++j) delete matrix[j];
    delete[] matrix;
    delete[] arr;
    delete number;
    return 0;
}