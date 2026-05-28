#ifndef __COMBINED_HPP_INCLUDED__
#define __COMBINED_HPP_INCLUDED__

#include "gift.hpp"
#include "teleport.hpp"

class combined : public gift, public teleport {
public:

    combined(uint32_t max_health, uint32_t heal_factor, uint32_t cell)
        : gift(max_health, heal_factor)
        , teleport(cell)
        , artifact()
        , health_empty(max_health > 0) {};

    virtual void draw() const override;
    virtual bool on_player_enter(player& p) override;

private:
    bool health_empty;
};

#endif