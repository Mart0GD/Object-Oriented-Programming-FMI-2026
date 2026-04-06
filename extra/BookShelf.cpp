#include "BookShelf.hpp"
#include <limits>

book_shelf::book_shelf(std::istream& is)
    : shelves_cnt(extract_int(is))
{
    if(!is || is.get() != '|') throw std::invalid_argument("Invalid data!");

    is >> pages_per_shelf;
    if(!is || is.get() != '\n') throw std::invalid_argument("Invalid data!");

    shelves = new shelf * [shelves_cnt]{};

    try
    {
        for (int i = 0; i < shelves_cnt; i++) shelves[i] = new shelf(is);
    }
    catch(const std::exception& e)
    {
        free();
        throw e;
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

book_shelf::book_shelf(int shelves_cnt, int pages_per_shelf)
    : shelves_cnt(shelves_cnt), pages_per_shelf(pages_per_shelf)
{
    if(shelves_cnt <= 0) throw std::invalid_argument("Invalid shelf count!");

    shelves = new shelf*[shelves_cnt]{};
    try
    {
        for (int i = 0; i < shelves_cnt; i++)
        {
            shelves[i] = new shelf(pages_per_shelf);
        }
    }
    catch(const std::exception& e)
    {
        free();
        throw e;
    }
}

book_shelf::book_shelf(const book_shelf& other)
    : shelves_cnt(other.shelves_cnt)
    , pages_per_shelf(other.pages_per_shelf)
{
    shelves = new shelf * [shelves_cnt]{};
    try
    {
        for (int i = 0; i < other.shelves_cnt; i++)
        {
            shelves[i] = new shelf(*other.shelves[i]);
        }
    }
    catch(const std::exception& e)
    {
        free(); throw e;
    }
}

book_shelf::~book_shelf() noexcept
{
    free();
}

bool  book_shelf::add_book(book*& new_book)
{
    for (int i = 0; i < shelves_cnt; i++)
    {
        book* ptr = new_book;
        if(shelves[i]->add(new_book)) {
            ptr->add_shelf(this);
            return true;
        }
    }
    
    return false;
}

book* book_shelf::remove_book(const char* name)
{
    for (int i = 0; i < shelves_cnt; i++) {
        book* to_remove = shelves[i]->remove(name);
        if(to_remove) return to_remove;
    }

    return nullptr;
}

found_info book_shelf::find(const char* name)
{
    for (int i = 0; i < shelves_cnt; i++)
    {
        int order = shelves[i]->find(name);
        if(order != -1)
        {
            return {i + i, order};
        }
    }
    
    return {-1,-1};
}

void book_shelf::resize(int new_pages_per_shelf)
{
    for (int i = 0; i < shelves_cnt; i++)
    {
        shelves[i]->resize(new_pages_per_shelf);
    }
    
}

void book_shelf::free() noexcept
{
    for (int i = 0; i < shelves_cnt; ++i) delete shelves[i];
    delete[] shelves;
}

void book_shelf::serialize(std::ostream& os, const book_shelf& val)
{
    os << val.shelves_cnt << '|' << val.pages_per_shelf << '\n';
    for (int i = 0; i < val.shelves_cnt; i++)
    {
        val.shelves[i]->serialize(os, *val.shelves[i]);
    }
    
}