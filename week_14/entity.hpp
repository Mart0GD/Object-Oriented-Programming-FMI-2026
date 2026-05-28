#ifndef __ENTITY_HPP_INCLUDED__
#define __ENTITY_HPP_INCLUDED__

#include "artifact.hpp"

#include <stdint.h>
#include <stdexcept>
#include <string.h>
#include <iostream>

class entity {
public:

    entity(const char* name, uint32_t health, uint32_t power);

    entity(const entity& other);
    entity& operator = (const entity& other);

    virtual ~entity() noexcept;

    void mod_health(int32_t new_val);

    inline uint32_t get_power() const { return power;}
    inline bool     is_alive()  const { return health > 0;}
    
protected:

    char* name;
    uint32_t max_health;
    int32_t  health;
    uint32_t power;

    bool alive;
};

class player : public entity {
public:
    player(const char* name, uint32_t health, uint32_t power)
        : entity(name, health, power)
    {
        if(power > MAX_POWER || power < MIN_POWER) throw std::invalid_argument("Invalid power value!");
        this->cell_index = 1;
    };

    virtual ~player() noexcept override = default;

    bool set_cell_index(uint32_t new_index);
    inline uint32_t get_cell_index() const { return cell_index; } 

private:
    static const uint32_t MAX_POWER = 100;
    static const uint32_t MIN_POWER = 20;

    int cell_index;
};



class enemy : public entity, public artifact {
public:
    enemy(const char* name, uint32_t health, uint32_t power)
        : entity(name, health, power)
    {
        if(power > MAX_POWER || power < MIN_POWER) throw std::invalid_argument("Invalid power value!");
    };

    virtual ~enemy() noexcept override = default;

    virtual void draw() const override;
    virtual bool on_player_enter(player& p) override;

private:
    static const uint32_t MAX_POWER = 50;
    static const uint32_t MIN_POWER = 1;
};
#endif