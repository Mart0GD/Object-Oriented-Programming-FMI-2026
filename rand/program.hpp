#pragma once
#include <fstream>
#include <limits>
#include <string.h>


enum function {
    UNKNOWN = -1,
    
    MOV,
    ADD,
    SUB,
    MUL,
    
    FUNCTIONS_CNT
};

static const int LETTERS_COUNT = 26;
static const char* function_names[FUNCTIONS_CNT] = 
{
    "MOV",
    "ADD",
    "SUB",
    "MUL"
};

struct program_context
{
    char* name = nullptr;

    int values[LETTERS_COUNT];
    bool defined[LETTERS_COUNT];
};

/*
*  0 --> програмата се е провлила
*  1 --> успяхме
*  -1 --> тотално се счупи
*/
int run_program(std::ifstream& is, program_context& ctx);
