#include <iostream>
#include <string.h>
using namespace std;

class Animal {
public:
    virtual ~Animal() = default;
    virtual void Talk() const = 0;
};

class Dog : public Animal {
public:
    virtual ~Dog() = default;
    virtual void Talk() const override { cout << "Love the world (;"; }
};

class Cat : public Animal {
public:
    Cat(const char* name, int age) : age(age), name(strcpy(new char[strlen(name) + 1], name)) {};
    // copy logic...
    virtual ~Cat() override { delete name; }

    virtual void Talk() const override { cout << "Gonna destroy the world!"; }
private:
    int age;
    char* name;
};

// Можете да напишете дефиниция единствено извън класа
void Animal::Talk() const
{
    std::cout << "Brrrrr...";
}