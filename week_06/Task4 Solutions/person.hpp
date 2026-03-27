#pragma once
#include <fstream>
#include "defines.hpp"

// forward delcaration or else we will have a circular dependancy
// person needs car, car needs person, so we just tell person that somewhere else a car class exists
// The actual logic for car is in the .cpp
class car;

class person {
public:

    person(const char* name, const char* EGN, const date& birth_date, sex _sex);
    ~person();

    bool set_name(const char* str);

    void print(std::ostream& os);
    void print_cars(std::ostream& os);

    bool add_car(car* what);
    bool remove_car(car* what);

    bool multi_car_owner() const { return cars_cnt > 1; }
    const char* get_egn()  const { return EGN;}
    int get_cars_cnt()     const { return cars_cnt; } 

private:

    void free();

    char* name;
    char* EGN;

    date birth_date;
    sex  _sex;

    car** cars;
    int cars_cnt, cars_size;

    bool valid;
};