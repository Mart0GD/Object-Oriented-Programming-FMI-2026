#include <iostream>
#include <new>
#include <string.h>
#include <stdexcept>

class Book{
public:
    Book() : author(nullptr), ISBN(nullptr), title(nullptr) {};
    Book(const char* author, const char* ISBN, const char* title)
        : Book() // --> делегиране на конструктор с цел валидни стойнсоти на полетата 
    {
        if(!set_string(this->author, author) ||
           !set_string(this->ISBN, ISBN)     ||
           !set_string(this->title, title))
        {
            free();
            throw std::invalid_argument("Invalid arguments!");
        }
    }

    Book(const Book& other) = delete; // не искаме да се копира, за илюстрационни цели
    Book(Book&& other)
        : Book() // --> делегиране на конструктор с цел валидни стойнсоти на полетата 
    {
        // Тук мога да използвам std::swap, защото делегираният конструктор е направил всяко поле nullptr.
        // След като излем от конструктора ще се извика деструктора на other и данните му ще се зачистят.
        // Ако имах неинициализирани адреси, деструктора на other щеше да хвърли segmentation fault!!
        std::swap(author, other.author);
        std::swap(ISBN, other.ISBN);
        std::swap(title, other.title);

        // може и така по ваша преценка 
        // author = other.author;
        // ISBN = other.ISBN;
        // title = other.title;

        // other.author = other.ISBN = other.title = nullptr;
    }

    ~Book() { free(); }


private:
    static bool set_string(char*& where, const char* what)
    {
        if(!what) return false;

        char* temp = new(std::nothrow) char[strlen(what) + 1];
        if(!temp) return false;

        strcpy(temp, what);
        delete[] where;
        where = temp;
        return true;
    } 

    void free() { delete[] author; delete[] ISBN; delete[] title; }

    char* author;
    char* ISBN;
    char* title;
};


int main(void)
{
    try
    {
        Book the_book_of_truth("Unknown", "???", "The Book Of Truth");
        Book thief(std::move(the_book_of_truth));
    }
    catch(const std::exception& e)
    {
        std::cout << e.what();
    }
    
    
    // Извикваме Move конструкотра с std::move
    
    // След този ред данните на the_book_of_truth са прехвърлени в thief, а всяко поле на the_book_of_truth е затрито, 
    // обекта е невалиден вече 
}