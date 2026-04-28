#include <iostream>

class Foo {
public:

    static int  sum (int a, int b) { return a + b; }
    static void print()            { std::cout << "Inside Foo"; } 
};

class Dir1 : private Foo {};

class Dir2 : public Dir1 {
public:

    void Bar()
    {
        // this->print(); --> 
        ::Foo::print();
    }
};

int main(){

    Dir2 d;
    d.Bar();

    return 0;
}