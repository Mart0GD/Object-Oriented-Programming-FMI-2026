#include <iostream>
#include <stdexcept>

class Array
{
    friend std::ostream& operator << (std::ostream& os, const Array& val);
    friend std::istream& operator >> (std::istream& os, Array& val);

private:
    int operator [] (int index) const
    {
        if(index >= cnt && index < 0)
        {
            throw std::invalid_argument("Invalid index!");
        }  

        return data[index];
    }

    int& operator [] (int index) 
    {
        if(index >= cnt && index < 0)
        {
            throw std::invalid_argument("Invalid index!");
        } 

        return data[index];
    }

    Array& operator += (const Array& b)
    {
        // concat
    }


    Array& operator ++ ()
    {
        for(int i = 0; i < cnt; ++i)
        {
            data[i] += 1;
        }

        return *this;
    }

    Array operator ++ (int)
    {
        Array copy(*this);

        ++(*this);
        return copy;
    }

private:
    int* data;
    int cnt, cap;
};

Array operator + (const Array& l, const Array& r)
{
    Array c(l);
    c += r;

    return c;
}

bool operator == (const Array& l, const Array& r)
{
    return l.cnt == r.cnt;
}

bool operator != (const Array& l, const Array& r)
{
    return !(l.cnt == r.cnt);
}

bool operator < (const Array& l, const Array& r)
{
    return l.cnt < r.cnt;
}

bool operator <= (const Array& l, const Array& r)
{
    return l < r || l == r;
}

bool operator >= (const Array& l, const Array& r)
{
    return !(l < r);
}

bool operator > (const Array& l, const Array& r)
{
    return l >= r && !(l == r);
}

std::ostream& operator << (std::ostream& os, const Array& val)
{
    if(!os) return os;

    os << val.cnt << '\n';
    for (int i = 0; i < val.cnt; i++)
    {
        os << val[i] << ' ';
    }
    
    return os;
}

std::istream& operator >> (std::istream& is, Array& val)
{
    if(!is) return is;


    int cnt;
    is >> cnt;

    for (int i = 0; i < cnt; i++)
    {
        int a;
        is >> a;
        val.push(a);
    }
    

    return is;
}


int main(void)
{
    int cnt;

    Array a;

    return 0;
}