#pragma once
#include <ostream>

template<typename T1, class T2>
struct pair{
    T1 val1;
    T2 val2;
};

template<typename T1, typename T2>
struct l_pair
{
    T1 (*f1)();
    T2 (*f2)();
};

#include "pair.inl"