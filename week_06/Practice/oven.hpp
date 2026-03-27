#pragma once
#include <fstream>

enum energy_class{
    UNKNOWN,

    A,
    B,
    AA
};

class oven{
public:

    oven();
    oven(const char* maker, int warranty, energy_class ec);
    oven(std::istream& is);
    ~oven();

private:

    bool set_string(char*& where, const char* what);

    void free();

    char* maker;
    char* country_of_origin;

    int warranty;

    energy_class ec;
    bool valid;
};