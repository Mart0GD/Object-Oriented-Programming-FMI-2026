#pragma once
#include "defines.hpp"
#include "person.hpp"

class car {
public:

    car(const char* model, const char* VIN, const date& dop, unsigned color, person* owner = nullptr);
    ~car();

    void chage_owner(person* new_owner);
    void print(std::ostream& os, bool print_owner = false);

    bool has_owner()      const { return owner; }
    const char* get_vin() const { return VIN; }

private:

    void free();
    char* model;
    char* VIN;

    date dop;
    unsigned color;
    person* owner;

    bool valid;
};