#include "Book.hpp"
#include <limits>
#include "BookShelf.hpp"

book::book(const char* name, const char* author, int pages)
    : ID(generate_ID())
    , name(nullptr)
    , author(nullptr)
    , pages(pages)
{
    if(!set_string(this->name, name) || !set_string(this->author, author))
    {
        free();
        throw std::invalid_argument("Invalid arguments passed");
    }

    increment_books_count();
}
book::book(std::istream& is)
    : ID(extract_string(is, '|'))
    , name(nullptr)
    , author(nullptr)
{
    if(!ID || !is || is.get() != '|') 
    {
        free();
        throw std::invalid_argument("Invalid input!");
    }

    name = extract_string(is,'|');
    if(!name || !is || is.get() != '|') 
    {
        free();
        throw std::invalid_argument("Invalid input!");
    }

    author = extract_string(is,'|');
    if(!author || !is || is.get() != '|') 
    {
        free();
        throw std::invalid_argument("Invalid input!");
    }

    is >> pages;
    if(!is)
    {
        free();
        throw std::invalid_argument("Invalid input!");
    }

    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

book::book(const book& other)
    : ID(copy_string(other.ID))
    , pages(other.pages)
    , name(nullptr)
    , author(nullptr)
{
    if(!set_string(name, other.name) || !set_string(author, other.author))
    {
        free();
        throw std::bad_alloc();
    }
    increment_books_count();
}
book& book::operator = (const book& other)
{
    if(this == &other) return *this;

    char* name_temp = copy_string(other.name);
    if(!name_temp) throw std::bad_alloc();

    char* author_temp = copy_string(other.author);
    if(!author_temp)
    {
        delete[] name_temp;
        throw std::bad_alloc();
    }

    delete[] name; delete[] author;
    name = name_temp;
    author = author_temp;
    pages = other.pages;

    return *this;
}

book::~book() noexcept 
{ 
    free(); 
    decrement_books_count();
}

void book::serialize(std::ostream& os, const book& val, bool include_shelf)
{
    os 
    << val.ID     << '|'
    << val.name   << '|'
    << val.author << '|'
    << val.pages;

    if (val.shelf && include_shelf)
    {
        found_info info = val.shelf->find(val.get_name());
        os << '|' << info.shelf  << '|'
                  << info.number << '|';
    }

    os << '\n';
}

bool book::change_name(const char* new_name) { return set_string(name, new_name);}

bool book::change_author(const char* new_author){ return set_string(author, new_author);}

char* book::generate_ID()
{
    if(id_generator    > 4000)          throw std::runtime_error("No unique id's left!");
    if(books_count + 1 > MAX_BOOKS_CNT) throw std::runtime_error("Max number of books exceeded!");

    char* str = new char[ID_LENGTH];
    strcpy(str, ID_TEMPLATE);

    static char unique_number[5];
    int current_id = id_generator++;

    for (int i = 0; i < 4; i++)
    {
        if(current_id == 0) {
            unique_number[3 - i] = '0';
            continue;
        }
        
        unique_number[3 - i] = current_id % 10 + '0';
        current_id /= 10;
    }
    unique_number[4] = '\0';

    strcpy(str + strlen(str), unique_number);
    return str;
}

void book::free() noexcept
{
    delete[] name;
    delete[] author;
    delete[] (char*)ID;

    name = author = nullptr;
}

int  book::books_count  = 0;
int  book::id_generator = 0;
const char book::ID_TEMPLATE[] = "IS-IF-";