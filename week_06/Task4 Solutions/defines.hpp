#pragma once
#include "string.h"
#include <new>

struct date {
    unsigned day;
    unsigned month;
    unsigned year;
};

enum sex {
    MALE,
    FEMALE
};

static const char* sex_strings[]
{
    "Male",
    "Female"
};

static bool set_string(char*& where, const char* what)
{
    if(!what || *what == '\0') return false;

    char* temp = new char[strlen(what) + 1];
    if(!temp) return false;

    strcpy(temp, what);
    delete[] where;
    where = temp;
    return true;
}

template<typename T>
static bool resize(T*& arr, int cnt, int new_size)
{
    T* new_arr = new(std::nothrow) T[new_size];
    if(!new_arr) return false;

    for (int i = 0; i < cnt; i++) new_arr[i] = arr[i];

    delete[] arr;
    arr = new_arr;
    return true;
}