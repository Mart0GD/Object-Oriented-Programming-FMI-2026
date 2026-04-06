#include "Book.hpp"
#include "BookShelf.hpp"
#include <fstream>

int main(void)
{
    // Copy constructor
    book* b1 = new book("Harry Potter", "J.K Rolling", 320);
    book* b2 = new book(*b1);

    // Assignment operator
    book* b3 = new book("peho", "s", 100);
    *b3 = *b2;

    // File I/O
    std::fstream ss("File.txt", std::ios::out | std::ios::in | std::ios::trunc);
    if(!ss) return -1;

    book::serialize(ss, *b3);
    ss.seekg(0);

    book b4(ss);

    book* b5 = new book("Good Book", "None", 100);
    book* b6 = new book("Good Book", "None", 10);
    book* b7 = new book("Good Book", "None", 10);

    book_shelf shelf(2, 430);
    shelf.add_book(b1);
    shelf.add_book(b2);
    shelf.add_book(b5);
    shelf.add_book(b6);
    shelf.add_book(b7);

    std::cout << shelf.find("Good Book").shelf;
    
    b5 = shelf.remove_book("Good Book");
    b6 = shelf.remove_book("Good Book");
    b7 = shelf.remove_book("Good Book");
    
    std::cout << shelf.find("Good Book").shelf;

    shelf.add_book(b5);
    shelf.add_book(b6);
    shelf.add_book(b7);

    shelf.resize(418);

    std::fstream shelf_s("File2.txt", std::ios::out | std::ios::in | std::ios::trunc);
    if(!shelf_s.is_open()) return -1;

    book_shelf::serialize(shelf_s, shelf);

    shelf_s.seekg(0);
    book_shelf shelf_2 = book_shelf(shelf_s);
    return 0;
}