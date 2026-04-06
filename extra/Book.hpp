#pragma once

#include <iostream>
#include <new>

#include "helpers.hpp"

class book_shelf;

class book{
public:

    book(const char* name, const char* author, int pages);
    book(std::istream& is);

    book(const book& other);
    book& operator = (const book& other);
    
    ~book() noexcept;
    
    static void         serialize(std::ostream& os, const book& val, bool include_shelf = false);

    bool                change_name(const char* new_name);
    bool                change_author(const char* new_author);

    void                add_shelf(book_shelf* shelf) { this->shelf = shelf; }

    inline const char*  get_name()   const { return name; }
    inline const char*  get_author() const { return author; }
    inline const char*  get_ID()     const { return ID; }
    inline int          get_pages()  const { return pages;}

private:
    void            free() noexcept;

    char*           name;
    char*           author;

    int             pages;
    const char*     ID;

private:
    static char*        generate_ID();

    static void         increment_books_count() { ++books_count; }
    static void         decrement_books_count() { --books_count; }

    static int          books_count;
    static int          id_generator;

    static const int    ID_LENGTH = 12;
    static const int    MAX_BOOKS_CNT = 500;
    static const char   ID_TEMPLATE[];

    book_shelf* shelf;
};