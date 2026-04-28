#include <string.h>

class Book {
public:

    Book(const char* name, int pages)
        : name(strcpy(new char[strlen(name) + 1], name))
        , pages(pages) {};

    Book(const Book& other) 
        : Book(other.name, other.pages) {};

    Book& operator = (const Book& other)
    {
        if(this != &other)
        {
            char* temp = strcpy(new char[strlen(other.name) + 1], other.name);
            delete[] name;
            name = temp;
            pages = other.pages;
        }

        return *this;
    }

    ~Book() { delete[] name; }

private:
    char* name;
    int pages;
};

enum color {
    RED,
    BROWN,
    ORANGE
};

class Leather_Book : public Book {
public:

    Leather_Book(const char* name, const char* leather_type, int pages, color c)
        : Book(name, pages) // --> делегиране на конструктор
    {
        /*
            Споменавам отново. При извикване на изключения се извикват деструктори 
            на всички инстанцирани обекти в сегашният scope, така че ако горният 
            делегиран конструктор премине и хвърлим изключение тук, ще бъде извикан деструктор на Book...
        */

        this->leather_type = strcpy(new char[strlen(leather_type) + 1], leather_type);
        this->c = c;
    }

    Leather_Book(const Leather_Book& other)
        : Book(other) // --> делегиране на копиращ конструктор 
    {
        this->leather_type = strcpy(new char[strlen(leather_type) + 1], leather_type);
        this->c = c;
    }

    Leather_Book& operator = (const Leather_Book& other)
    {
        if(this != &other)
        {
            char* temp = strcpy(new char[strlen(leather_type) + 1], other.leather_type);

            /* 
            *   Тази операция може да се провали, но Book отговаря сам за данните си.
            *   Тук нищо не зачистваме
            */
            try { Book::operator= (other); }
            catch(...)
            {
                delete[] temp;
                throw;
            }
            
            delete[] leather_type;
            leather_type = temp;
            c = other.c;
        }

        return *this;
    } 

    /*
        Не извикваме деструктора на Book, при изтриване на обект се изтриват
        данните от долу нагоре, така че от най-долния клас до основния
    */
    ~Leather_Book() { delete[] leather_type; }

private:
    color c;
    char* leather_type;
};