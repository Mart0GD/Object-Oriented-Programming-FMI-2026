#include <iostream>
#include <fstream>  // we will be reading and writing -> include fstream

#include "program.hpp"

int main(void){
    char filename[MAX_FILE_NAME]; 

    // read the file name from the console
    std::cout << "Insert file name: ";
    std::cin.getline(filename, MAX_FILE_NAME);

    std::ifstream is(filename);
    if(!is.is_open())
    {
        std::cout << "Invalid file name!\n";
        return -1;
    }

    // automatically creates the file, if it exists it wipes its data
    std::ofstream os("Result.txt");
    if(!os.is_open())
    {
        std::cout << "Could not create Result file!";
        is.close();
        return -1;
    }

    // while there is something to read
    while(is)
    {
        program_context current_context;
        int res = read_program(current_context, is);

        if(res == 1) // success
        {
            os << current_context.program_name << '\n';

            for(int i = 0; i < ALPHABET_SIZE; ++i)
            {
                if(current_context.defined[i])
                {
                    os 
                    << (char)('a' + i)
                    << '='
                    << current_context.values[i] << '\n';
                }
            }
        }
        else if(res == 0) os << current_context.program_name << ' ' << FAIL_MESSAGE << '\n';

        clear_context(current_context);
    }

    is.close();
    os.close();
    return 0;
}