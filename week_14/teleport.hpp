#ifndef __TELEPORT_HPP_INCLUDED__
#define __TELEPORT_HPP_INCLUDED__

#include "artifact.hpp"
#include <stdint.h>
#include <iostream>

class teleport : public virtual artifact {
public:

    teleport(uint32_t cell);

    teleport(const teleport& other) = delete;
    teleport& operator = (const teleport& other) = delete;

    virtual void draw() const override;
    virtual bool on_player_enter(player& p) override;

protected:
    static uint32_t next_id;
    static uint32_t get_next_id() { return next_id++; }

    const int32_t id;
    uint32_t cell;
};

#endif
