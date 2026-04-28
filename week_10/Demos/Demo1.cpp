#include <iostream>

class Foo
{
    public:
    void print_p() { std::cout << "Inside public A"; }

    protected:
    int a;
    void print_prt() { std::cout << "Inside protected A"; }

    private:
    void print_prv() { std::cout << "Inside private A"; }
};

/*
    Всеки от следващите наследени класове има достъп до всички член данни
    които са в public и protected секцията на базовия клас

    Public    данни --> public
    Protected данни --> protected
    Private   данни --> private
*/
class Dir1 : public Foo {
public:

    void foo() {
        Foo::print_p();
        Foo::print_prt();
        // A::print_prv(); --> до този нямаме достъп
        
        // Може и без scope оператора 
        print_p();
        print_prt(); 
        // print_prv(); --> нямаме достъп
    }
};

/*
    Public    данни --> protected
    Protected данни --> protected
    Private   данни --> private
*/
class Dir2 : protected Foo {
public:

    void foo() {
        Foo::print_p();
        Foo::print_prt();
        // A::print_prv(); 
        
        print_p();
        print_prt(); 
        // print_prv(); 
    }
};

/*
    Public    данни --> private
    Protected данни --> private
    Private   данни --> private
*/
class Dir3 : private Foo {
public:

    void foo() {
        Foo::print_p();
        Foo::print_prt();
        // A::print_prv(); 

        print_p();
        print_prt(); 
        // print_prv();
    }
};

int main(){

    Dir1 a;
    Dir2 b;
    Dir3 c;

    // Имаме достъп от Dir1 до публичните функции на Foo
    a.print_p();

    // Публичните данни на Foo вече са protected за външния свят
    // b.print_p(); --> невалиден код!

    // Публичните данни на Foo вече са private за външния свят
    // c.print_p(); --> невалиден код

    return 0;
}