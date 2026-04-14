#include <iostream>
#include <math.h>

struct Vector2D{
private:
    friend std::ostream& operator << (std::ostream& os, const Vector2D& val);
    friend std::istream& operator >> (std::istream& is, Vector2D& val);
public:
    Vector2D(double x, double y) : x(x), y(y) {};
    double x, y;

    Vector2D& operator += (const Vector2D& other)
    {
        this->x += other.x;
        this->y += other.y;

        return *this;
    }

    Vector2D& operator - ()
    {
        this->x = - this->x;
        this->y = - this->y;
    }

    operator double() const
    {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    operator bool() const 
    {
        return this->x != 0 && this->y != 0;
    }

    bool operator ! () const 
    {
        return !(*this);
    } 

    Vector2D& operator ++ ()
    {
        this->x += 1;
        this->y += 1;
        return *this;
    }

    Vector2D operator + (int)
    {
        Vector2D copy(*this);
        ++(*this);
        return copy;
    }
};

std::ostream& operator << (std::ostream& os, const Vector2D& val)
{
    os << val.x << ' ' << val.y;
    return os;
}

std::istream& operator >> (std::istream& is, Vector2D& val) 
{
    is >> val.x >> val.y;
    return is;
}

Vector2D operator + (const Vector2D& l, const Vector2D& r)
{
    Vector2D res(l);
    res += r;
    return res;
}

double operator * (const Vector2D& l, const Vector2D& r)
{
    return l.x * r.x + l.y * r.y;
}

bool operator && (const Vector2D& f, const Vector2D s)
{
    return f.x != 0 && f.y != 0 && s.x != 0 && s.y != 0;
}

bool operator == (const Vector2D& l, const Vector2D& r)
{
    return abs((double)l - (double)r) <= 0.000000000001;
}

bool operator != (const Vector2D& l, const Vector2D& r)
{
    return !(l == r);
}

bool operator < (const Vector2D& l, const Vector2D& r)
{
    return (double)l < (double)r;
}

bool operator <= (const Vector2D& l, const Vector2D& r)
{
    return l < r || l == r;
}

bool operator >= (const Vector2D& l, const Vector2D& r)
{
    return !(l < r);
}

bool operator > (const Vector2D& l, const Vector2D& r)
{
    return l >= r && l != r;
}

int main(){

    Vector2D v1(0,0);
    Vector2D v2(1,1);
    Vector2D v3(13, 15);

    double res = v3 * (v1 + v2);
    v1 += v2;
    Vector2D v4 = v1 + v2;
}

