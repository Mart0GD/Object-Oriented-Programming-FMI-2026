#include <iostream>
using namespace std;

struct Person {
    Person(int age) : age(age) {};

    int age;
    void foo() { cout << "I am a Person"; }
};

struct Teacher : public Person {
    Teacher(int age, int years_of_teaching)
        : Person(age), years_of_teaching(years_of_teaching) {};

    int years_of_teaching;
};

struct Pilot : public  Person {
    Pilot(int age, int flight_hours)
        : Person(age), flight_hours(flight_hours) {};

    int flight_hours;
};

struct Flight_Instructor : public Teacher , public Pilot {
    Flight_Instructor(int age, int flight_hours, int years_of_teaching, float hour_rate)
        : Teacher(age, years_of_teaching), Pilot(age, flight_hours), hour_rate(hour_rate) {};

    float hour_rate;
};


int main(void){
    Flight_Instructor* pesho = new Flight_Instructor{10, 100, 4, 45};

    // Валидно
    Pilot* pilot_pesho      = static_cast<Pilot*>(pesho);
    Teacher* teacher_pesho  = static_cast<Teacher*>(pesho);

    // Невалидно --> коя част от Person да вземе, като пилот или като учител?
    // Person* person_pesho1    = static_cast<Person*>(pesho);

    // Така вече е валидно 
    Person* person_pesho     = static_cast<Person*>(static_cast<Teacher*>(pesho));

    // Сега обратното пак е невалидно
    // Flight_Instructor* pesho_back = static_cast<Flight_Instructor*>(person_pesho);

    // Но можем да вземем обратно учителската част 
    Flight_Instructor* pesho_back = static_cast<Flight_Instructor*>(static_cast<Teacher*>(pesho_back));

    return 0;
}