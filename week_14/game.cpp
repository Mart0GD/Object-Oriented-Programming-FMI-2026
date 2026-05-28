#include "game.hpp"

#include "entity.hpp"
#include "gift.hpp"
#include "teleport.hpp"
#include "combined.hpp"
#include "entity.hpp"

char read_answer()
{
    char answer;
    do
    {
        std::cin.get(answer);
        if(answer != 'f' && answer != 'b') std::cin.clear();
        else break;

    } while (true);
    
    return answer;
}

void game::begin_game(const char* map_filename)
{
    std::ifstream is(map_filename);
    if(!is.is_open()) return;

    if(!read_map(is)) 
    {
        free_map();
        return;
    }

    player pesho("OOP Master", 100, 42);

    do
    {
        std::cout << "Forwards (f) or backwords (b)? (Index " << pesho.get_cell_index() << ")\n"; 
        char answer = read_answer();

        if(answer == 'f') pesho.set_cell_index(pesho.get_cell_index() + 1);
        else {      
            if(pesho.get_cell_index() - 1== 0) 
            {
                std::cout << "Out of map, try again!\n";
                continue;
            }

            pesho.set_cell_index(pesho.get_cell_index() - 1);
        }

        if(pesho.get_cell_index() == 100) break;

        do
        {
            int index = pesho.get_cell_index();
            artifact* cell = field[index - 1];
            if(!cell) break;

            bool res = cell->on_player_enter(pesho);
            cell->draw();

            if(!res) 
            {
                delete field[index - 1]; 
                field[index - 1] = nullptr;
            }

            if(index == pesho.get_cell_index()) break;
        } while (true);

    } while (pesho.is_alive() && pesho.get_cell_index() != 100);
    
    if(pesho.is_alive()) std::cout << "You won!\n";
    else                 std::cout << "Try again!\n";

    free_map();
}


bool game::read_map(std::ifstream& is)
{
    // g --> health
    // t --> teleport
    // c --> combined
    // w --> weak monster
    // s --> strong monster 
    // * --> nothing
    for (int i = 0; i < MAX_FIELDS; i++)
    {
        char symb = is.get();
        if(!is) return false;

        switch (symb)
        {
            case '*': field[i] = nullptr; break;
            case 'g': field[i] = new gift(100, 20); break;
            case 't': field[i] = new teleport(i + 1); break;
            case 'c': field[i] = new combined(100, 20, i + 1); break;
            case 'w': field[i] = new enemy("weakling", 40, 20); break;
            case 's': field[i] = new enemy("bjorn", 60, 40); break;
            default: std::cout << "Unknwon symbol!"; return false;
        }
    }
    
    return true;
}


void game::free_map() noexcept
{
    for (int i = 0; i < MAX_FIELDS; i++) delete field[i];
}