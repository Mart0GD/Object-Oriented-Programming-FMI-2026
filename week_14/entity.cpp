#include "entity.hpp"

#include "game.hpp"

entity::entity(const char* name, uint32_t health, uint32_t power)
    : name(nullptr)
    , max_health(health)
    , health(health)
    , power(power)
    , alive(true)
{
    if(!name || *name == '\0') throw std::invalid_argument("Empty name!");

    this->name = strcpy(new char[strlen(name) + 1], name);
}

entity::entity(const entity& other)
    : entity(other.name, other.health, other.power) 
{
    health = other.health; // защото по принцип се слага на максисмум 
};

entity& entity::operator = (const entity& other)
{
    if(this != &other)
    {
        char* temp = strcpy(new char[strlen(other.name) + 1], other.name);

        delete[] name;
        name = temp;
        health = other.health;
        max_health = other.max_health;
    }

    return *this;
}

entity::~entity() noexcept { delete[] name; }

void entity::mod_health(int32_t val)
{
    int32_t new_hp = health + val;
    if(new_hp >= (int32_t)max_health) health = max_health;
    else                     health = new_hp;

    if(health <= 0) alive = false;
}


void enemy::draw() const
{
    std::cout 
    << "Enemy: " << name  << ", "
    << " Power: " << power << ", "
    << " Max health: " << max_health << ", "
    << " Current health: " << health  << '\n';
}

bool enemy::on_player_enter(player& p)
{
    p.mod_health(-power);
    this->mod_health(-p.get_power());
    if(!alive) std::cout << "Monster Killed!\n";

    return alive;
}

bool player::set_cell_index(uint32_t new_index)
{
    if(new_index > game::MAX_FIELDS && new_index <= 0) return false;
    this->cell_index = new_index;
    return true;
}