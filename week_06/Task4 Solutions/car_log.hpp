#pragma once
#include "car.hpp"
#include "person.hpp"

class car_log {
public:

    car_log(car** cars, int cars_cnt, person** people, int people_cnt);
    ~car_log();

    // all of the methods will have console output
    void get_owners_of_multiple_cars();
    void cars_without_owners();
    void cars_of_person(const char* egn);
    void people_with_number_of_cars(int number);

    bool sell(const char* VIN, const char* EGN);


private:

    person* find_person(const char* egn);
    car*    find_car(const char* vin);

    car** cars;
    int cars_cnt;

    person** people;
    int people_cnt;
};