#pragma once
#include <istream>
#include <string.h>

static char*               extract_string(std::istream& is, char delim = ' ')
{
    int buffer = 32;

    char* str = new char[buffer];
    if(!str) return nullptr;

    int iter = 0;
    while (is && is.peek() != delim)
    {
        if(iter + 2 == buffer)
        {
            char* temp = new char[buffer * 2];
            if(!temp) 
            {
                delete[] str;
                return nullptr;
            }
            delete[] str;
            str = temp;
            buffer *= 2;
        }

        str[iter++] = (char)is.get();
    }
    str[iter] = '\0';

    return str;
}

static char*               copy_string(const char* what)
{
    if(!what || *what == '\0') return nullptr;

    char* temp = new(std::nothrow) char[strlen(what) + 1];
    if(!temp) return nullptr;

    strcpy(temp, what);
    return temp;
}

static bool                set_string(char*& where, const char* what)
{
    if(!what || *what == '\0') return false;

    char* temp = copy_string(what);
    if(!temp) return false;

    delete[] where;
    where = temp;

    return true;
}

static int extract_int(std::istream& is)
{
    int i;
    is >> i;
    return i;
}