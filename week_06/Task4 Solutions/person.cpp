#include "person.hpp"
#include "car.hpp"
#include <string.h>

person::person(const char* name, const char* EGN, const date& birth_date, sex _sex)
    : name(nullptr)
    , EGN(nullptr)
    , birth_date(birth_date)
    , _sex(_sex)
    , cars(nullptr)
    , cars_cnt(0)
    , cars_size(1)
{
    cars = new(std::nothrow) car * [cars_size];
     
    if( !cars                           || 
        !set_string(this->name, name)   || 
        !set_string(this->EGN, EGN))
    {
        free();
        valid = false;
        return;
    }
}

person::~person() { free(); }

bool person::set_name(const char* str) { return set_string(this->name, str); }

bool person::add_car(car* what)
{
    if(!what) return false;
    if(cars_cnt + 1 >= cars_size) {
        resize(cars, cars_cnt, cars_size * 2); 
        cars_size *= 2;
    }

    int pos = 0;
    while (pos < cars_cnt && cars[pos]) {++pos;}
    
    cars[pos] = what;
    ++cars_cnt;

    return true;
}

bool person::remove_car(car* what)
{
    if(!what) return false;

    int pos = 0;
    while(pos < cars_cnt && cars[pos] != what) { ++pos; }
    if(pos == cars_cnt) return false;
    
    cars[pos] = nullptr;
    --cars_cnt;
    return true;
}

void person::print(std::ostream& os)
{
    os 
    << name << ' '
    << EGN << ' '
    << birth_date.day << '\\' << birth_date.month << '\\' << birth_date.year << ' '
    << sex_strings[_sex] << '\n';      
}

void person::print_cars(std::ostream& os)
{
    os << "Cars of " << name << ":\n";

    for (int i = 0; i < cars_cnt; i++) cars[i]->print(os);
}

void person::free()
{
    delete[] name; name = nullptr;
    delete[] EGN; EGN = nullptr;

    int count = cars_cnt;
    for (int i = 0; i < count; i++)
    {
        cars[i]->chage_owner(nullptr);
        cars[i] = nullptr;
    }
    
    delete[] cars; cars = nullptr;
}