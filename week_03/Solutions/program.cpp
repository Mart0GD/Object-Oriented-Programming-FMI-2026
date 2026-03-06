#include "program.hpp"
#include <limits>

void read_to_str(std::ifstream& is, const char str[] = END_LINE)
{
    const int buffer_size = 1024;
    char buffer[buffer_size];

    do
    {
        is >> std::ws; // skips whitespace
        is.getline(buffer, buffer_size);
    } while (is && strcmp(buffer, str) != 0);
}

char* read_str(std::ifstream& is, char delim)
{
    int buffer = 1024;

    char* temp = new(std::nothrow) char[buffer];
    if(!temp) return nullptr;

    int c;
    int iter = 0;
    while ((c = is.get()) != EOF && c != delim && c != '\n')
    {
        if(iter + 1 == buffer)
        {
            char* resize = new(std::nothrow) char[buffer * 2];
            if(!resize)
            {
                delete[] temp; temp = nullptr;
                return nullptr;
            }
            strcpy(resize, temp);
            delete[] temp; 
            temp = resize;
        }

        temp[iter++] = c;
    }

    temp[iter] = '\0';
    return temp;
}

bool is_letter(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

char to_lower(char c){
    return c >= 'a' && c <= 'z' ? c : c + 32;
}

int execute_cmd(program_context& ctx, std::ifstream& is)
{
    const int buffer_size = 1024;
    char buffer[buffer_size];
    
    // try and parse the end of the program
    std::streampos pos = is.tellg();
    is >> std::ws;
    is.getline(buffer, buffer_size);

    if(strstr(buffer, END_LINE)) return 2;
    else is.seekg(pos, std::ios::beg);

    // try to parse a command
    is >> std::ws;
    is.getline(buffer, buffer_size, '('); // read until an opening brace
    if(!is) return 0; 

    commnad cmd = commnad::UNKNOWN;
    for(int i = 0; i < COMMANDS_CNT; ++i)
    {
        if(strcmp(buffer, commands_names[i]) == 0)
        {
            cmd = (commnad)i;
            break;
        }
    }

    char comma;
    char symb;

    is >> symb >> comma;
    if(!is || comma != ',' || !is_letter(symb)) return 0; // syntax error

    switch (cmd)
    {
        case MOV:{
            
            char var;
            is >> var;
            if(is_letter(var))
            {
                var = to_lower(var);

                // no such variable defined -> error
                if(!ctx.defined[var - 'a']) return 0;

                ctx.defined[to_lower(symb) - 'a'] = 1;
                ctx.values[to_lower(symb) - 'a'] = ctx.values[var - 'a'];
            }
            else{
                is.putback(var);
                int val;
                is >> val;

                ctx.defined[to_lower(symb) - 'a'] = 1;
                ctx.values[to_lower(symb) - 'a'] = val;
            }
        }break;

        case ADD:{
            if(!ctx.defined[symb - 'a']) return 0;

            char var;
            is >> var;
            if(is_letter(var))
            {
                var = to_lower(var);

                // no such variable defined -> error
                if(!ctx.defined[var - 'a']) return 0;
                
                ctx.values[to_lower(symb) - 'a'] += ctx.values[var - 'a'];
            }
            else{
                is.putback(var);
                int val;
                is >> val;

                ctx.values[to_lower(symb) - 'a'] += val;
            }
            
        }break;

        case SUB:{
            if(!ctx.defined[symb - 'a']) return 0;

            char var;
            is >> var;
            if(is_letter(var))
            {
                var = to_lower(var);

                // no such variable defined -> error
                if(!ctx.defined[var - 'a']) return 0;
                
                ctx.values[to_lower(symb) - 'a'] -= ctx.values[var - 'a'];
            }
            else{
                is.putback(var);
                int val;
                is >> val;

                ctx.values[to_lower(symb) - 'a'] -= val;
            }

        }break;

        case MUL:{
            if(!ctx.defined[symb - 'a']) return 0;

            char var;
            is >> var;
            if(is_letter(var))
            {
                var = to_lower(var);

                // no such variable defined -> error
                if(!ctx.defined[var - 'a']) return 0;
                
                ctx.values[to_lower(symb) - 'a'] *= ctx.values[var - 'a'];
            }
            else{
                is.putback(var);
                int val;
                is >> val;

                ctx.values[to_lower(symb) - 'a'] *= val;
            }
        }break;

        default: return 0; // unknown command
    }

    char end_brace;
    is >> end_brace;
    if(!is || end_brace != ')') return 0;

    return 1;
}

int read_program(program_context& ctx, std::ifstream& is)
{
    const int buffer_size = 1024;
    char buffer[buffer_size];

    do
    {
        is >> std::ws;
        is.getline(buffer, buffer_size, ' '); // places a '\0' at the end

        if(strcmp(buffer, "PROGRAM") == 0) break;
        if(!is) return -1;
        
        // skips until it sees a newline 
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (true);

    is >> std::ws;
    ctx.program_name = read_str(is, ' '); // allocate memory for the name

    if(!ctx.program_name) return -1;

    do
    {
        /*
        * 0 --> invalid syntax
        * 1 --> cmd executed successfully
        * 2 --> end
        */
        int res = execute_cmd(ctx, is);
        if(res == 2) break;
        else if(res == 0){
            read_to_str(is);
            return 0;
        }
    } while (true);
    
    return 1;
}