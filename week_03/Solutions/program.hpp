#pragma once

#include <fstream>
#include <string.h>

#include "constants.hpp"


struct program_context{
    char* program_name{nullptr};

    bool defined[ALPHABET_SIZE]{};
    int  values[ALPHABET_SIZE]{};
};

/*
*   returns 1 on success
*   returns 0 on program fail
*   returns -1 on fatal
*/
int read_program(program_context& ctx, std::ifstream& is);

inline void clear_context(program_context& ctx) { if(ctx.program_name) delete[] ctx.program_name; }