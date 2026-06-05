#include "command.hpp"
#include "command.hpp"
#include <limits>

const command* command_factory::get_command(std::istream& is)
{
    for(const command* cmd : commands)
    {
        if(cmd->can_read(is)) {
            return cmd;
        }
    }
    
}