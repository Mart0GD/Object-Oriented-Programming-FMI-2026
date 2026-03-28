#include <string.h>
#include <new>

class Person{
public:

    explicit Person(bool sex, int age = 20, const char* str = "John Doe")
        : sex(sex)
        , age(age)
        , name(copy_str(str)) {};

    Person(const Person&)               = delete;
    Person& operator = (const Person&)  = delete;

    ~Person() { delete[] name; } 

private:
    static char* copy_str(const char* what)
    {
        if(!what) return nullptr;

        char* temp = new(std::nothrow) char[strlen(what) + 1];
        if(!temp) return nullptr;

        strcpy(temp, what);
        return temp;
    }

    const char* name;
    int age;
    bool sex; // 1 за мъж, 0 за жена
};


int main(void)
{
    // Това създава обект от тип Person с име John doe, години 20 и пол мъж
    //Person pesho = 1;

    // Това създава обект от тип Person с име John doe, години 20 и пол жена
    //Person peshka = 0;

    // Ако пред конструктора я нямаше думата explicit кода тук щеше да е позволен,
    // за да не стават грешки оабче, се е добавила думата explicit, за да не може това 
    // създаване на обекти да е валидно!
}