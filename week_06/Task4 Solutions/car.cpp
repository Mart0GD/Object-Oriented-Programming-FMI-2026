#include "car.hpp"

car::car(const char* model, const char* VIN, const date& dop, unsigned color, person* owner)
    : model(nullptr)
    , VIN(nullptr)
    , dop(dop)
    , color(color)
    , owner(nullptr)
    , valid(true)
{
    char mask = 15;
    if((color & (mask << (3 * 8))) > 0)
    {
        valid = false;
        return;
    }

    if(!set_string(this->model, model) || !set_string(this->VIN, VIN))
    {
        free();
        valid = false;
        return;
    }

    if(owner) chage_owner(owner);
}

car::~car() { free(); }

void car::chage_owner(person* new_owner)
{
    if(owner) owner->remove_car(this);

    if(new_owner) new_owner->add_car(this);
    owner = new_owner;
}
void car::print(std::ostream& os, bool print_owner)
{
    char red = color & ((1 << 8) - 1);
    char green = (color >> 8) & ((1 << 8) - 1);
    char blue = (color >> 16) & ((1 << 8) - 1);

    os << model << ' '
       << VIN << ' '
       << dop.day << '/' << dop.month << '/' << dop.year << ' '
       << "color: " << "( " << red << ',' << green << ',' << blue << ") ";
    
    if(owner && print_owner) owner->print(os);
    else os << '\n';
}

void car::free()
{
    if(owner) {
        owner->remove_car(this);
        owner = nullptr;
    }

    delete[] model; model = nullptr;
    delete[] VIN; VIN = nullptr;
}