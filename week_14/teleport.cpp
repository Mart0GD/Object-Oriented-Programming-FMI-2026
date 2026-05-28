#include "teleport.hpp"
#include "game.hpp"
#include "entity.hpp"

teleport::teleport(uint32_t cell)
    : cell(cell), id(get_next_id()) {};

void teleport::draw() const
{
    std::cout 
    << "Teleport: "
    << " ID: " << id
    << " Cell: " << cell << '\n';
}

bool teleport::on_player_enter(player& p)
{
    int dir = rand() % 2;
    int new_pos = -1;

    if(dir == 1) // right
    {
        int dist = game::MAX_FIELDS - cell;

        new_pos = cell + (rand() % (dist + 1));
    }
    else new_pos = rand() % cell;

    p.set_cell_index(new_pos);
    std::cout << "Teleported at index " << new_pos << '\n'; 

    return true;
}

uint32_t teleport::next_id = 0;