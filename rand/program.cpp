#include "program.hpp"

bool is_letter(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char to_lower(char c)
{
    return c >= 'A' && c <= 'Z' ? c + 32 : c;
}

int run_program(std::ifstream& is, program_context& ctx)
{
    const int buffer_size = 1024;
    char buffer[buffer_size];

    
    do
    {
        is >> std::ws;
        is.getline(buffer, buffer_size, ' ');

        if(!is) return -1;
        if(strcmp(buffer, "PROGRAM") == 0) break;

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (true);

    is.getline(buffer, buffer_size, ' ');
    if(!is) return -1;

    ctx.name = new(std::nothrow) char[strlen(buffer) + 1];
    if(!ctx.name) return -1;
    
    strcpy(ctx.name, buffer);
    is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    if(!is) return -1;

    do
    {
        is.getline(buffer, buffer_size, '(');
        if(!is) return 0;

        function func = UNKNOWN;
        for (int i = 0; i < FUNCTIONS_CNT; ++i)
        {
            if(strcmp(buffer, function_names[i]))
            {
                func = (function)i;
                break;
            }
        }

        char symb;
        char comma;

        is >> symb >> comma;
        if(!is || !is_letter(symb) || comma != ',') return 0;

        switch (func)
        {
            case MOV:{  
                char c;

                is >> c;
                if(!is) return 0;

                if(is_letter(c))
                {
                    char low = to_lower(c);

                    if(!ctx.defined[low - 'a']) return 0;

                    ctx.defined[symb - 'a'] = 1;
                    ctx.values[symb - 'a'] = ctx.values[symb - 'a'];
                }
                else {
                    is.putback(symb);

                    int number;
                    is >> std::ws >> number;
                    if(!is) return 0;

                    ctx.defined[symb - 'a'] = 1;
                    ctx.values[symb - 'a'] = number;
                }
            }break;

            case ADD:{
                if(!ctx.defined[symb - 'a']) return 0;

                char c;
                is >> c;
                if(!is) return 0;

                if(is_letter(c))
                {
                    char low = to_lower(c);

                    if(!ctx.defined[low - 'a']) return 0;

                    ctx.values[symb - 'a'] += ctx.values[symb - 'a'];
                }
                else {
                    
                    is.putback(symb);

                    int number;
                    is >> std::ws >> number;
                    if(!is) return 0;

                    ctx.values[symb - 'a'] += number;
                }
            }break;
            
            case SUB:{
                if(!ctx.defined[symb - 'a']) return 0;

                char c;
                is >> c;
                if(!is) return 0;

                if(is_letter(c))
                {
                    char low = to_lower(c);

                    if(!ctx.defined[low - 'a']) return 0;

                    ctx.values[symb - 'a'] -= ctx.values[symb - 'a'];
                }
                else {
                    is.putback(symb);

                    int number;
                    is >> std::ws >> number;
                    if(!is) return 0;

                    ctx.values[symb - 'a'] -= number;
                }
            }break;

            case MUL:{
                if(!ctx.defined[symb - 'a']) return 0;

                char c;
                is >> c;
                if(!is) return 0;

                if(is_letter(c))
                {
                    char low = to_lower(c);

                    if(!ctx.defined[low - 'a']) return 0;

                    ctx.values[symb - 'a'] *= ctx.values[symb - 'a'];
                }
                else {
                    is.putback(symb);

                    int number;
                    is >> std::ws >> number;
                    if(!is) return 0;

                    ctx.values[symb - 'a'] *= number;
                }
            }break;

            default: return 0;
        }

        char brace;
        is >> brace;
        if(!is || brace != ')') return 0;
        
    } while (true);


    return 1;
}