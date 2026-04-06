#pragma once
#include "Book.hpp"

class shelf {
public:

    shelf();
    shelf(std::istream& is);
    shelf(int pages);

    shelf(const shelf& other);
    shelf& operator = (const shelf& other) = delete;

    ~shelf() noexcept;

    int         find(const char* name);
    bool        add(book*& new_book);

    book*       remove(const char* name);
    void        resize(int new_cap);


    static void serialize(std::ostream& os, const shelf& shelf);

private:
    void        free();

    book**      pages;
    int         capacity, count;
};