#include "game.hpp"

int main(){
    srand(time(NULL));
    
    game& session = game::get_instance();
    session.begin_game("map.txt");
}
