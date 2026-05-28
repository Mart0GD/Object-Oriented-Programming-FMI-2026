#include <iostream>
template<typename Type, int cmp>
bool eqs(const Type& a)
{
    return a == cmp;
}

template<class Type, size_t size>
class Array{

    Type[size];
};

template<class T>
class dynamic_array{

    dynamic_array();
    dynamic_array(size_t cap);

    dynamic_array(const dynamic_array& other);
    dynamic_array(dynamic_array&& other);

    dynamic_array& operator= (const dynamic_array& other);

    dynamic_array& operator= (dynamic_array&& other);

    ~dynamic_array() noexcept;
    

    class iterator;

    iterator begin() { return iterator(data);}
    iterator end()   { return iterator(data + cnt); }

private:
    T* data;

    size_t cap;
    size_t cnt;
};


template<typename T>
class dynamic_array<T>::iterator {
public:

    dynamic_array(T* ptr) : ptr(ptr) {};

    bool operator == (const iterator& other)
    {
        return ptr == other.ptr;
    }

    bool operator != (const iterator& other)
    {
        return !(ptr == other.ptr);
    }

    iterator& operator ++ ()
    {
        ++ptr;
        return *this;
    }

    iterator operator ++ (int)
    {
        iterator copy(*this);
        ++(*this);
        return copy;
    }

    T& operator * () const { return *ptr; }

    T* operator -> () { return ptr; }

private:
    T* ptr;
};

#include "practice.inl"
