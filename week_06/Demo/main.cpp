#include "Student.hpp"

#include <iostream>

int main() {
    Student s1("Ivan", 20);

    s1.setName("Petar");
    s1.setAge(22);

    std::cout << s1.getName() << " " << s1.getAge() << std::endl;

    return 0;
}