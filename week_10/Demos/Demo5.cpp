#include <iostream>

class A {
public:
    int a;
    void print() { std::cout << 's'; }
};

class B : public A{

    public:
    int b;
    void print() { std::cout << 'p'; }
};


int main()
{
    B b;
    b.A::print();
    
    A a;
    a.print();

    int size = sizeof(B);
    return 0;
}