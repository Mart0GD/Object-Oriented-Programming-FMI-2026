#include "car_log.hpp"
#include <string.h>
#include <iostream>

car_log::car_log(car** cars, int cars_cnt, person** people, int people_cnt)
    : cars(cars), people(people), cars_cnt(cars_cnt), people_cnt(people_cnt)  { }

car_log::~car_log()
{
    cars = nullptr;
    people = nullptr;
}

// all of the methods will have console output
void car_log::get_owners_of_multiple_cars()
{
    std::cout << "Owners of multiple cars: \n";

    for (int i = 0; i < people_cnt; i++)
        if(people[i]->multi_car_owner()) { people[i]->print(std::cout); }
}
void car_log::cars_without_owners()
{
    std::cout << "Cars without owners: \n";

    for (int i = 0; i < cars_cnt; i++)
        if(!cars[i]->has_owner()) cars[i]->print(std::cout);
}
void car_log::cars_of_person(const char* egn)
{
    person* p = find_person(egn);
    if(!p)
    {
        std::cout << "No such person in the records!";
        return;
    }

    p->print_cars(std::cout);
}
void car_log::people_with_number_of_cars(int number)
{
    std::cout << "People with " << number << " cars: \n";

    for (int i = 0; i < people_cnt; i++)
        if(people[i]->get_cars_cnt() == number) people[i]->print(std::cout);
}

bool car_log::sell(const char* VIN, const char* EGN)
{
    person* p = find_person(EGN);
    car* c = find_car(VIN);

    if(!p || !c) return false;

    c->chage_owner(p);
    return true;
}

person* car_log::find_person(const char* egn)
{
    person* p = nullptr;
    for (int i = 0; i < people_cnt; i++)
    {
        if(strcmp(people[i]->get_egn(), egn) == 0)
        {
            p = people[i];
            break;
        }
    }

    return p;
}

car*    car_log::find_car(const char* vin)
{
    car* c = nullptr;
    for (int i = 0; i < cars_cnt; i++)
    {
        if(strcmp(cars[i]->get_vin(), vin) == 0)
        {
            c = cars[i];
            break;
        }
    }

    return c;
}