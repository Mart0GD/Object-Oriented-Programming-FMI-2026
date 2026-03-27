#include "car_log.hpp"

int main(void)
{
    person p2("Ivan", "8001012345", {1,1,1980}, sex::MALE);
    car c2("Audi", "5678", {12,5,2010}, 150, &p2);

    person p3("Maria", "9052156789", {15,2,1990}, sex::FEMALE);
    car c3("Mercedes", "1234", {3,7,2018}, 220, &p3);

    person p4("Georgi", "8504301122", {30,4,1985}, sex::MALE);
    car c4("Toyota", "5678", {20,9,2015}, 130, &p4);

    person p5("Elena", "9203123456", {12,3,1992}, sex::FEMALE);
    car c5("Honda", "10221", {11,11,2012}, 140, &p5);

    person p6("Dimitar", "7807077777", {7,7,1978}, sex::MALE);
    car c6("Ford", "FF2020", {1,6,2020}, 160, &p6);

    person p7("Nikol", "9901010000", {1,1,1999}, sex::FEMALE);
    car c7("Volkswagen", "VW9999", {25,12,2008}, 120, &p7);

    person p8("Stoyan", "8303033333", {3,3,1983}, sex::MALE);
    car c8("Peugeot", "PE1234", {14,2,2016}, 110, &p8);

    car c9("Renault", "RN5678", {9,9,2011}, 115);
    car c10("Skoda", "SK2468", {30,8,2019}, 125);
    car c11("Opel", "OP1357", {17,4,2007}, 105);

    // person* test = new person("p", "1", {1,1,1}, FEMALE);

    // c9.chage_owner(test);
    // c10.chage_owner(test);

    // delete test;

    c9.chage_owner(&p8);

    person** people = new person*[7];

    people[0] = &p2;
    people[1] = &p3;
    people[2] = &p4;
    people[3] = &p5;
    people[4] = &p6;
    people[5] = &p7;
    people[6] = &p8;

    car** cars = new car*[10];

    cars[0] = &c2;
    cars[1] = &c3;
    cars[2] = &c4;
    cars[3] = &c5;
    cars[4] = &c6;
    cars[5] = &c7;
    cars[6] = &c8;
    cars[7] = &c9;
    cars[8] = &c10;
    cars[9] = &c11;

    car_log log(cars, 10, people, 7);

    log.cars_of_person(p2.get_egn());
    log.cars_without_owners();
    log.get_owners_of_multiple_cars();
    log.people_with_number_of_cars(2);

    log.sell(c10.get_vin(), p2.get_egn());
    log.people_with_number_of_cars(2);


    delete[] people;
    delete[] cars;
    return 0;
}