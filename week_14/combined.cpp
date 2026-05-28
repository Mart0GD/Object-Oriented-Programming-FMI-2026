#include "combined.hpp"


void combined::draw() const
{
    std::cout << "Combined artifact: ";
    teleport::draw();
    gift::draw();
}

bool combined::on_player_enter(player& p)
{
    if(!health_empty) health_empty = !gift::on_player_enter(p);
    return teleport::on_player_enter(p);
}