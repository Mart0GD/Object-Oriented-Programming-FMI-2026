#include "pair.hpp"
#include <fstream>

#include <string.h>

inline bool prefix(const char* str1, const char* str2)
{
    if(!str1 || !str2) return false;

    while(*str2 && *str1)
    {
        if(*str1 != *str2) return false;
        ++str1; ++str2;
    }

    return *str2 || (!*str1 && !str2);
}

// str1 suffix str2 
// a abba
inline bool suffix(const char* str1, const char* str2)
{
    if(!str1 || !str2) return false;

    const char* start1 = str1;
    const char* start2 = str2;

    str1 += strlen(str1) - 1;
    str2 += strlen(str2) - 1;

    while(str1 >= start1 && str2 >= start2)
    {
        if(*str1 != *str2) return false;
        --str1; --str2;
    }

    return str2 != start2 || (str1 == start1 && str2 == start2);
}



//Функции add, mult, sub, 
template<class T1, class T2>
inline void add(pair<T1,T2>& p1, pair<T1,T2>& p2)
{
    p1.val1 += p2.val1;
    p1.val2 += p2.val2;
}

//Функции add, mult, sub, 
template<class T1, class T2>
inline void mult(pair<T1,T2>& p1, pair<T1,T2>& p2)
{
    p1.val1 *= p2.val1;
    p1.val2 *= p2.val2;
}

//Функции add, mult, sub, 
template<class T1, class T2>
inline void sub(pair<T1,T2>& p1, pair<T1,T2>& p2)
{
    p1.val1 -= p2.val1;
    p1.val2 -= p2.val2;
}

// Функции <=, >=, <, >, == със стандартното им значение за почленно сравняване на наредени двойки.
template<class T1, class T2>
inline bool l(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
    return p1.val1 < p2.val1 && p1.val2 < p2.val2;
}

template<class T1, class T2>
inline bool m(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
    return p1.val1 > p2.val1 && p1.val2 > p2.val2;
}

template<class T1, class T2>
inline bool eq(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
    return p1.val1 == p2.val1 && p1.val2 == p2.val2;
}

template<class T1, class T2>
inline bool neq(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
    return !eq(p1,p2);
}

template<class T1, class T2>
inline bool leq(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
    return l(p1,p2) || eq(p1,p2);
}

template<class T1, class T2>
inline bool meq(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
    return m(p1,p2) || eq(p1,p2);
}


template<class T1, class T2>
inline void display(const pair<T1,T2>& p, std::ostream& os)
{
    os << "( " << p.val1 << ", " << p.val2 << ")\n";
}

//Направете специализация на функцията display, за тип <char*, char*>, така че ако val1 е префикс на val2 или val2 е суфикс на 
// val1, то да се запиша само по големият стринг от двата, да се наслоят един върху друг.

template<>
inline void display(const pair<const char*, const char*>& p, std::ostream& os)
{
    os << "( ";   
    if(prefix(p.val1,p.val2)) os << p.val2;
    else if(suffix(p.val2, p.val1)) os << p.val1;
    else os << p.val1 << ", " << p.val2;

    os << ")";
}