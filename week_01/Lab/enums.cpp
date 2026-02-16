#include "iostream"

// define an enum
enum shape
{
    S_UNKNOWN = -1,

    S_CIRCLE,
    S_SQUARE,
    S_TRIANGLE,
    S_PENTAGON,

    S_SHAPES_CNT
};

// define an enum as a new type
typedef enum car
{
    C_UNKNOWN,

    C_BMW,
    C_MERCEDES,
    C_HONDA,
    C_MITUBISHI,

    C_CARS_CNT
} car;

// anonymous enum
// They are used most commonly to same up on memory.
// All the values inside the scope are compile time constants
enum
{
    CAT     = 1,
    DOG     = 2,
    MOUSE   = 3,
    BULL    = 4,
} type; // we can name it as a global variable


// class enum (scoped enumration)
// The purpose of scoped enums is to prevent name collisons.
// The values inside this enum are encapulated, so in order to access them we need to do the following:
// names::Pesho, names::Gosho
enum class name
{
    Pesho,
    Gosho,
    Genadi,
    Provadi,
    Petar,
    CAT,        // here we have no collison with the CAT value inside the annonymous enum
};

int main()
{
    car my_car = C_BMW;
    shape my_fav_shape = S_SQUARE;
    int value = CAT;

    name my_name = name::CAT;
}
