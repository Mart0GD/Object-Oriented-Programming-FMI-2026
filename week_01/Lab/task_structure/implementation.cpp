#include "implementation.hpp"
#include "consts.hpp"


namespace department 
{
    void run()
    {
        // using a const variable inside another namespace
        std::cout << consts::INITIAL_POLICE_OFFICERS;

        std::cout << "We are inside the implementation";
    }
}