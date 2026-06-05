#pragma once
#include <vector>
#include <iostream>

class command;

class command_factory {
public:

    static command_factory& get_inst()
    {
        static command_factory inst;
        return inst;
    }

    void add_command(const command* cmd) { commands.push_back(cmd); }

    const command* get_command(std::istream& is);

private:
    command_factory() = default;
    command_factory(const command_factory&);
    command_factory& operator=(const command_factory&);

    
    std::vector<const command*> commands;
};