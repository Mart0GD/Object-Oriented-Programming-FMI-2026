#include <string.h>
#include<iostream>

class Book {
public:
    Book() : text(nullptr) {};
    Book(const char* text)
    {
        if(!text) throw std::invalid_argument("Invalid data!");

        this->text = new char[strlen(text) + 1];
        strcpy(this->text, text);
    };    

    // Дефинираме копиращ конструктор
    Book(const Book& other)
    {
        text = new char[strlen(other.text) + 1];
        strcpy(text, text);
    }

    // Забелязахте ли колко много логиката си прилича с конструктора? Нека преизползваме малко логика (;
    // Book(const Book& other)
    //     : Book(other.text) {};

    ~Book() 
    { 
        delete[] text; 
        text = nullptr;
    }

private:
    char* text; 
};

int main(void){

    try
    {
        Book bible("And there was light!");

        {
            // Извикване експлицитно на служебен копиращ конструктор 
            Book necronomicon(bible); 
        } // --> край на блока, извиква се деструктор на necronomicon

        // Какво става тук??
        // necronomicon изтри своето собстевно копие на данните на bible
        // Това вече е желан ефект => Успех!!
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
};