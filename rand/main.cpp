
#include "program.hpp"

#include <iostream>
#include <fstream>


int main(void)
{   
    char filename[1024];
    std::cin.getline(filename, sizeof(filename));

    std::ifstream is(filename);
    if(!is.is_open()) return -1;

    std::ofstream os("Result.txt");
    if(!os.is_open())
    {
        is.close();
        return -1;
    }


    do
    {
        program_context ctx;
        int res = run_program(is, ctx);

        if(res == 1) { // success 
            os << ctx.name << ":\n";

            for(int i = 0; i < LETTERS_COUNT; ++i)
            {
                if(ctx.defined[i])
                {
                    os 
                    << (char)('a' + i)
                    << " = "
                    << ctx.values[i] << '\n';
                }
            }
        }
        else if (res == 0) {
            os << ctx.name << ' ' << "ERROR\n";
        }

        delete[] ctx.name;
    } while (is);
    
    is.close();
    os.close();
    return 0;
}