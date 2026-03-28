#include <new>
#include <stdexcept>

class Circle{
public:
    Circle& operator = (const Circle& other)
    {
        if(this != &other){
            radius = other.radius;
            c_x    = other.c_x;
            c_y    = other.c_y;
        }

        return *this;
    };

private:
    int radius { 1 };
    int c_x    { 0 };
    int c_y    { 0 };
};

// какво става ако има динамични данни
class Stack{
public:
    Stack(int cap = 10)
        : cap(cap)
        , tos(0)
    {
        data = new int[cap]{};
    }

    Stack(const Stack& other) = delete;  // за илюстрационна цел
    Stack(Stack&& other)      = delete;

    Stack& operator = (const Stack& other)
    {
        if(this == &other) return *this;

        int* temp = new int[other.cap]{};
        for (int i = 0; i < other.cap; i++)
        {
            temp[i] = other.data[i];
        }
         
        delete[] data;
        data = temp;
        cap  = other.cap;
        tos = other.tos;

        return *this;
    }

    Stack& operator = (Stack&& other)
    {
        if(this == &other) return *this;

        std::swap(data, other.data);
        std::swap(tos, other.tos);
        std::swap(cap, other.cap);

        return *this;
    }

    ~Stack() { delete[] data;}

    void add(int elem)
    {
        if(tos == cap) throw std::invalid_argument("Full!");
        data[tos++] = elem;
    }

    int remove()
    {
        if(tos == 0) throw std::invalid_argument("Empty!");
        int val = data[tos--];
        return val;
    }

private:
    int* data;
    int tos, cap;
};

int main(){
    // Извикване на конструктор по подразбиране 
    Circle c1;

    // Извикване на копиращ конструктор 
    Circle c2 = c1;

    // Извикване на конструктор по подразбиране
    Circle c3;

    // Извикване на оператор за присвояване!!
    c3 = c2;

    Stack s1(10);
    s1.add(1);
    s1.add(2);

    Stack s2;
    s2.add(2);
    s2.add(10000);

    // s2 придобива стойностите на s1
    s2 = s1;

    Stack s3;
    s3.add(10);
    s3.add(12);
    s3.add(1000);

    // 1) Стойностите на s2 се прехвърлят на s3
    // 2) Стойностите на s3 се прехвърлят на s2
    // 3) Извиква се деструктор на s2 и данните на s3 изчезват! 
    s3 = std::move(s2);

    return 0;
};