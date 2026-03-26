#include "Student.hpp"
#include <new>

Student::Student(const char* name, int age) 
    : valid(true), name(nullptr), age(0)
{
    if(!setName(name) || !setAge(age))
    {
        valid = false;
        return;
    }
}

bool Student::setName(const char* newName)
{
    if(!newName) return false;

    char* temp = new(std::nothrow) char[strlen(newName) + 1];
    if(!temp) return false;

    strcpy(temp, newName);

    delete[] name;
    name = temp;
    return true;
}

bool Student::setAge(int newAge) {
    if(age < 0 || age > 120) return false;
    this->age = newAge;
    return true;
}