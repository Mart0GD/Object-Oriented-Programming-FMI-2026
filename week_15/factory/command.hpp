#pragma once
#include <istream>
#include "string.h"
#include "factory.hpp"
#include <limits>

enum cmd {
    UNKNOWN,

    ADD,
    SUB,
    MULT,
    DIV,

    CNT
};



class command{
public:
    command(const char* name)
        : name(name){} 

    virtual ~command() noexcept = default;

    virtual bool can_read(std::istream& is) const
    {
        std::streampos pos = is.tellg();

        char buffer[1024];

        is.getline(buffer, 1024, '(');
        if(!is || strcmp(buffer, name) != 0)
        {
            is.seekg(pos);
            return false;
        }

        return true;
    }

    virtual bool calculate(std::istream& is, int& val) const = 0;

protected:
    const char* name;
};

class registrator {
public:
    registrator(const command* cmd)
    {
        command_factory::get_inst().add_command(cmd);
    }
};

class add : public command, public registrator {
public:

    add()
        : command("add"), registrator(this) {}

    virtual bool calculate(std::istream& is, int& val) const override
    {
        int a;
        is >> a;
        if(!is) return false;

        if(is.get() != ',') return false;

        int b;
        is >> b;
        if(!is) return false;

        if(is.get() != ')') return false;

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        val = a + b;
        return true;
    }
};


class sub : public command, public registrator {
public:

    sub()
        : command("sub"), registrator(this) {}

    virtual bool calculate(std::istream& is, int& val) const override
    {
        int a;
        is >> a;
        if(!is) return false;

        if(is.get() != ',') return false;

        int b;
        is >> b;
        if(!is) return false;

        if(is.get() != ')') return false;

        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        val = a - b;
        return true;
    }
};

class mult : public command, public registrator{
public:

    mult()
        : command("mult"), registrator(this) {}

    virtual bool calculate(std::istream& is, int& val) const override
    {
        int a;
        is >> a;
        if(!is) return false;

        if(is.get() != ',') return false;

        int b;
        is >> b;
        if(!is) return false;

        if(is.get() != ')') return false;


        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        val = a * b;
        return true;
    }
};

class divide : public command, public registrator {
public:

    divide()
        : command("add"), registrator(this) {}

    virtual bool calculate(std::istream& is, int& val) const override
    {
        int a;
        is >> a;
        if(!is) return false;

        if(is.get() != ',') return false;

        int b;
        is >> b;
        if(!is || b == 0) return false;

        if(is.get() != ')') return false;


        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        val = a / b;
        return true;
    }
};

class pow : public command, public registrator{
public:
    pow()
        : command("pow"), registrator(this) {}

    virtual bool calculate(std::istream& is, int& val) const override
    {
        int a;
        is >> a;
        if(!is) return false;

        if(is.get() != ')') return false;


        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        val = a * a;
        return true;
    }
};