#ifndef __GAME_HPP_INCLUDED__
#define __GAME_HPP_INCLUDED__

#include "artifact.hpp"

#include <stdint.h>
#include <fstream>

class game {
public:
    static const uint32_t MAX_FIELDS = 100;

    static game& get_instance()  
    {
        static game inst;
        return inst;
    } 

    void begin_game(const char* map_filename);

private:
    game() = default;
    game(const game& other) = default;
    game& operator = (const game& other) = default;

    bool read_map(std::ifstream& is);
    void free_map() noexcept;

private:
    artifact* field[MAX_FIELDS]{};
};

#endif