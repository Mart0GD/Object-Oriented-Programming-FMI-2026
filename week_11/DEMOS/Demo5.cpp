#include <iostream>
#include <string.h>
using namespace std;

class Animal {
public:
    virtual ~Animal() = default;
    virtual void Talk() const = 0;

    // Това ние ще наричаме виртуален конструктор
    virtual Animal* clone() const = 0;
};

class Dog : public Animal {
public:
    virtual ~Dog() = default;
    virtual void Talk() const override { cout << "Love the world (;"; }

    virtual Dog* clone() const override { return new Dog(*this); }
};

class Cat : public Animal {
public:
    Cat(const char* name, int age) : age(age), name(strcpy(new char[strlen(name) + 1], name)) {};
    // copy logic...
    virtual ~Cat() override { delete name; }

    virtual void Talk() const override { cout << "Gonna destroy the world!"; }

    virtual Cat* clone() const override { return new Cat(*this); }
private:
    int age;
    char* name;
};

int main(){
    Animal* animal[3]{};

    Cat* joe = new Cat("Joe", 10);
    animal[0] = joe;
    animal[1] = joe->clone();
    animal[2] = new Dog();

    for(int i = 0; i < 3; ++i) delete animal[i];
    return 0;
}