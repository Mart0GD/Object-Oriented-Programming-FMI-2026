#include "Shelf.hpp"

shelf::shelf(std::istream& is) {
    is >> count;
    if(!is || is.get() != '\n') throw std::invalid_argument("Invalid input");

    for (int i = 0; i < count; ++i)
    {
        book* b = new book(is);
        add(b);
    }
}

shelf::shelf() 
    : pages(nullptr)
    , capacity(0)
    , count(0) {}

shelf::shelf(int pages)
    : capacity(pages)
    , count(0)
{
    this->pages = new book * [pages]{};
}

shelf::shelf(const shelf& other)
    : shelf(other.capacity)
{
    this->count = other.count;

    try
    {
        for (int i = 0; i < other.capacity; i++)
        {
            if(!other.pages[i]) continue;

            pages[i] = new book(*other.pages[i]);
            for (int j = 1; j < pages[i]->get_pages(); j++)
            {
                pages[i + j] = pages[i];
            }
            i += pages[i]->get_pages() - 1;
        }
        
    }
    catch(const std::exception& e)
    {
        free();
        throw e;
    }
    
    
}

shelf::~shelf() noexcept
{
    free();
}

void shelf::free()
{
    for (int i = 0; i < capacity; i++)
    {
        if(pages[i])
        {
            book* to_remove = pages[i];
            for (int j = i; j < i + to_remove->get_pages(); j++) pages[j] = nullptr;
            delete to_remove;
        }
    }
}

int shelf::find(const char* name)
{
    int cnt = -1;
    for (int i = 0; i < capacity; i++)
    {
        if(!pages[i]) continue;

        if(strcmp(name, pages[i]->get_name()) != 0) 
        {
            i += pages[i]->get_pages() - 1;
            ++cnt;
        }
        else break;
    }
    
    return cnt;
}

bool shelf::add(book*& new_book)
{
    for (int i = 0; i < capacity; i++)
    {
        if(pages[i]) {
            i += pages[i]->get_pages() - 1;
            continue;
        }
        
        int start = i;
        int end   = i + 1;
        for(; end < capacity && !pages[end]; ++end);

        if(end - start < new_book->get_pages()) i = end - 1;
        else {
            for(; i < start + new_book->get_pages(); ++i) { pages[i] = new_book; }
            
            new_book = nullptr;
            ++count;
            return true;
        }
    }
    
    return false;
}

book* shelf::remove(const char* name)
{
    book* removed = nullptr;
    for (int i = 0; i < capacity; i++)
    {
        if(!pages[i]) continue;

        if(strcmp(pages[i]->get_name(), name) != 0) 
        {
            i += pages[i]->get_pages() - 1;
            continue;
        }

        removed = pages[i];
        int pages_to_clear = removed->get_pages();

        for (int j = 0; j < pages_to_clear; j++)  {
            if (i + j < capacity)  pages[i + j] = nullptr;
        }

        --count;
        return removed;
    }
    return nullptr;
}

void shelf::resize(int new_cap)
{
    if (new_cap == capacity) return;

    if (new_cap < capacity)
    {
        for (int i = new_cap; i < capacity; i++)
        {
            if (pages[i]) remove(pages[i]->get_name());
        }
    }

    book** pages_temp = new book*[new_cap]{}; 

    int elements_to_copy = (new_cap < capacity) ? new_cap : capacity;
    for (int i = 0; i < elements_to_copy; i++)
    {
        pages_temp[i] = pages[i];
    }

    delete[] pages;
    pages = pages_temp;
    capacity = new_cap;
}

void shelf::serialize(std::ostream& os, const shelf& shelf)
{
    os << shelf.count << '\n';
    for (int i = 0; i < shelf.capacity; i++)
    {
        if(!shelf.pages[i]) continue;

        book::serialize(os, *shelf.pages[i]);
        i += shelf.pages[i]->get_pages() - 1;
    }
}