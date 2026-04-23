#pragma once
#include <iostream>
#include <string.h>

static char* copy_from_stream(std::istream& is, char delim = '|')
{
    if(!is) return nullptr;
    int buffer = 256;

    char* str = new(std::nothrow) char[buffer];
    if(!str) return nullptr;
    
    int symb, iter = 0;
    while (is.peek() != EOF && is.peek() != delim)
    {
        if(iter + 2 == buffer)
        {
            char* temp = new(std::nothrow) char[buffer * 2 + 1];
            if(!temp) 
            {
                delete[] str;
                return nullptr;
            }
            strcpy(temp, str);
            delete[] str;
            str = temp;
            buffer *= 2;
        }

        str[iter++] = (char)is.get();
    }

    str[iter] = '\0';
    return str;
}


static char* copy_string(const char* str)
{
    if(!str || *str == '\0') return nullptr;

    char* temp = new(std::nothrow) char[strlen(str) + 1];
    if(!temp) return nullptr;

    strcpy(temp, str);
    return temp;
}