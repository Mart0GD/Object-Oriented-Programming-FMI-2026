#include "factory.hpp"
#include <fstream>
#include "command.hpp"


int main(){


    command_factory& fact = command_factory::get_inst();

    std::ifstream is("commands.txt");

    const command* cmd = fact.get_command(is);
    int res;
    cmd->calculate(is, res);

    std::cout << res << '\n';

    return 0;
}