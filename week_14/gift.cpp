#include "gift.hpp"

gift::gift(uint32_t max_health, uint32_t heal_factor)
    : max_health(max_health)
    , heal_factor(heal_factor)
    , health(max_health) { }

void gift::draw() const
{
    std::cout 
    << "Gift: "
    << "Max health: " << max_health
    << " Heal factor: " << heal_factor << '\n';
}

bool gift::on_player_enter(player& p)
{
    uint32_t value = this->health > heal_factor ? heal_factor : health;
    p.mod_health(value);

    this->health -= heal_factor;
    return this->health > 0;
}