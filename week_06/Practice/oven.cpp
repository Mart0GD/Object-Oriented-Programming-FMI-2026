#include "oven.hpp"
#include <string.h>
#include <new>

oven::oven()
    : maker(nullptr)
    , country_of_origin(nullptr)
    , warranty(0)
    , ec(UNKNOWN) 
    , valid(true)  {}

oven::oven(const char* maker, int warranty, energy_class ec)
    : country_of_origin(nullptr)
    , maker(nullptr)
    , warranty(warranty)
    , ec(energy_class::UNKNOWN)
    , valid(true)
{
    if(!maker){
        valid =false;
        return;
    }

    if(ec == energy_class::UNKNOWN){
        this->valid = false;
        return;
    }

    if(!set_string(this->maker, maker) || !set_string(this->country_of_origin, country_of_origin))
    {
        valid = false;
        free();
        return;
    }
}


oven::oven(std::istream& is)
    : oven()
{
    char buffer[1024];

    is.getline(buffer, 1024, ' ');
    if(!is) {
        valid = false;
        return;
    }

    if(!set_string(maker, buffer))
    {
        valid = false;
        return;
    }

    is.getline(buffer, 1024, ' ');
    if(!is) {
        valid = false;
        free();
        return;
    }

    if(!set_string(country_of_origin, buffer))
    {
        valid = false;
        free();
        return;
    }

    int energy_c;
    is >> warranty >> energy_c;
    this->ec = (energy_class)energy_c; 
}

bool oven::set_string(char*& where, const char* what)
{
    if(!what || *what == '\0') return false;

    char* temp = new(std::nothrow) char[strlen(what) + 1];
    if(!temp) return false;

    strcpy(temp, what);
    delete where;
    where = temp;

    return true;
}

oven::~oven()
{
    free();
}

void oven::free() {
    delete[] maker;
    delete[] country_of_origin;   
}