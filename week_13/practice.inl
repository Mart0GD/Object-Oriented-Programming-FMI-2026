#include <algorithm>

template<typename T>
dynamic_array<T>::dynamic_array()
    : data(nullptr)
    , cnt(0)
    , cap(0)
{ }

template<typename T>
dynamic_array<T>::dynamic_array(size_t cap)
    : data(nullptr)
    , cnt(0)
    , cap(cap)
{
    data = new T [cap];
}

template<typename T>
dynamic_array<T>::dynamic_array(const dynamic_array& other)
{
    this->data = new T[other.cap];

    try
    {
        for (int i = 0; i < other.cnt; i++)
        {
            data[i] = other.data[i];
        }
    }
    catch(const std::exception& e)
    {
        delete[] this->data;
        throw e;
    }
    
}

template<typename T>
dynamic_array<T>& dynamic_array<T>::operator= (dynamic_array&& other)
{
    if(this != &other)
    {
        std::swap(this->data, other.data);
        std::swap(this->cap, other.cap);
        std::swap(this->cnt, other.cnt);
    }

    return *this;
}

template<typename T>
dynamic_array<T>::dynamic_array(dynamic_array&& other)
{
    data = other.data;
    cap = other.cap;
    cnt = other.cnt;

    other.data = nullptr;
}

template<typename T>
dynamic_array<T>& dynamic_array<T>::operator= (const dynamic_array& other)
{
    if(this != &other)
    {
    //     T* temp = new T[other.cnt];

    //     try
    //     {
    //         for (int i = 0; i < count; i++)
    //         {
    //             temp[i] = other.data[i];
    //         }
            
    //     }
    //     catch(const std::exception& e)
    //     {
    //        delete[] temp;
    //        throw e;
    //     }

    //     delete[] this->data;
    //     this->data = temp;
    //     cap = other.cnt;
    //     cnt = other.cnt;

        dynamic_array<T> copy = other;
        *this = std::move(copy);
    }

    return *this;
}

template<typename T>
dynamic_array<T>::~dynamic_array() noexcept
{
    delete[] data;
}