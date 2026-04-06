#pragma once

#include <iostream>

#include "Shelf.hpp"

struct found_info 
{
    int shelf;
    int number;
};

class book_shelf{
public:

    book_shelf(std::istream& is);
    book_shelf(int shelves_cnt = 3, int pages_per_shelf = 200);

    book_shelf(const book_shelf& other);
    book_shelf& operator = (const book_shelf& other) = delete;

    ~book_shelf() noexcept;

    bool        add_book(book*& new_book);
    book*       remove_book(const char* name);

    found_info  find(const char* name);
    void        resize(int new_pages_per_shelf);

    static void serialize(std::ostream& os, const book_shelf& val);

private:
    void        free() noexcept;

    shelf**     shelves;

    int         pages_per_shelf;
    const int   shelves_cnt;
};