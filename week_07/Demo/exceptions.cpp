#include <stdexcept>
#include<iostream>
#include <string.h>

class Book {
public:
    Book(const char* title, const char* author)
        : title(nullptr)
        , author(nullptr)
    {
        // Тук нямаме проблеми, само new може да хвърли изключение и ще го обработим, 
        // но памет заделена няма да има...
        this->title = strcpy(new char[strlen(title) + 1], title);

        this->author = new(std::nothrow) char[strlen(author) + 1];
        if(!this->author)
        {
            // зачистваме си ресурсите и излизаме
            // Ако new се провали, то хвърля bad_alloc, следователно и ние това ще хвърлим...
            delete[] this->title;
            throw std::bad_alloc();
        }
        
        strcpy(this->author, author);
    }
    
    Book(const Book& other)
        : Book(other.title, other.author) {}

    Book& operator = (const Book& other)
    {
        if(this == &other) return *this;

        char* temp1 = strcpy(new char[strlen(other.title) + 1], other.title);
        char* temp2 = new(std::nothrow) char[strlen(other.author) + 1];
        if(!temp2)
        {
            delete[] temp1;
            throw std::bad_alloc();
        }

        delete[] title;
        delete[] author;

        title = temp1;
        author = temp2;
        return *this;
    }

    ~Book() { delete[] title; delete[] author; }

private:
    char* title;
    char* author;
};

int main(void) {

    try{
        Book b1("Moby-Dick", "Herman Melville");
    }
    catch(const std::exception& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }

    return 0;
}