#ifndef __GIFT_HPP_INCLUDED__
#define __GIFT_HPP_INCLUDED__

#include "artifact.hpp"
#include "entity.hpp"
#include <stdint.h>
#include <iostream>

class gift : public virtual artifact {
public:

    gift(uint32_t max_health, uint32_t heal_factor);

    virtual void draw() const override;
    virtual bool on_player_enter(player& p) override;

protected:
    uint32_t max_health;
    uint32_t health;
    
    uint32_t heal_factor;
};

#endif
