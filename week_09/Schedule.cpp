#include "Schedule.hpp"
#include "helpers.hpp"
#include <string.h>

Schedule::Schedule(const char* name)
    : name(nullptr)
{
    if(!set_name(name))
    {
        throw std::invalid_argument("Invalid name passed!");
    }
}

Schedule::Schedule(const Schedule& other)
    : Schedule(other.name)
{
    try
    {
        for (int i = 0; i < SLOTS; i++)
        {
            if(other.data[i])

            data[i] = new Task(*other.data[i]);
            for(int j = 1; j < data[i]->get_length(); ++j)
            {
                data[i + j] = data[i];
            }

            i += data[i]->get_length() - 1;
        }
    }
    catch(const std::exception& e)
    {
        free();
        throw e;
    }
}

Schedule& Schedule::operator = (const Schedule& other)
{
    if(this != &other) return *this;

    char* name_cpy = strcpy(new char[strlen(other.name) + 1], other.name);

    Task** tasks_cpy = new(std::nothrow) Task * [SLOTS]{};
    if(!tasks_cpy){
        delete[] name_cpy;
        throw std::bad_alloc();
    }

    try
    {
        for (int i = 0; i < SLOTS; i++)
        {
            if(other.data[i])

            tasks_cpy[i] = new Task(*other.data[i]);
            for(int j = 1; j < data[i]->get_length(); ++j)
            {
                tasks_cpy[i + j] = tasks_cpy[i];
            }

            i += tasks_cpy[i]->get_length() - 1;
        }
    }
    catch(const std::exception& e)
    {
        for (int i = 0; i < SLOTS; i++) delete data[i];
        delete[] name;
        throw e;
    }

    free();
    name = name_cpy;
    
    for (int i = 0; i < SLOTS; i++)
    {
        data[i] = tasks_cpy[i];
        tasks_cpy[i] = nullptr;
    }

    delete[] tasks_cpy;
    return *this;
}

Schedule::~Schedule() noexcept {  free(); }

bool Schedule::add_task(const Task& to_add, unsigned hours, unsigned minute)
{
    // ## too long --> goes to the next day
    if(hours * 60 + minute + to_add.get_length() > SLOTS) return false;

    // ## check for a task with higher or equal priority
    int start = hours * 60 + minute;
    for (int i = 0; i < to_add.get_length(); i++)
        if(data[start + i] && to_add.get_priority() <= data[start + i]->get_priority()) return false;
    
    Task* heap_copy = new(std::nothrow) Task(to_add);
    if(!heap_copy) return false;

    for (int i = 0; i < to_add.get_length(); i++)
    {
        if(!data[start + i])
        {
            data[start + i] = heap_copy;
            continue;
        }

        // ## make way for our task
        remove_task(data[start + i]);
        --i;
    }
    
    return true;
}

bool  Schedule::print_tasks_in_hour(unsigned hour)
{
    if(hour > 23) return false;

    std::cout 
    << "\nPrinting tasks in hour " << hour << ":\n"
    << "------------------------------------\n";

    int start = hour * 60;
    for(int i = 0; i < 60; ++i) {
        if(data[start + i]){
            std::cout 
            << "Description: " << data[start + i]->get_description() << '\n'
            << "Priority   : " << data[start + i]->get_priority()    << '\n'
            << "Time       : " << data[start + i]->get_length()      << '\n'
            << "Finished   : " << data[start + i]->finished()        << '\n'
            << "--\n";

            i += data[start + i]->get_length() - 1;
        }   
    }

    return true;
}

Task* Schedule::get_task(unsigned hour, unsigned minute)
{
    if(hour * 60 + minute < SLOTS) return data[hour * 60 + minute];
    throw std::invalid_argument("Invalid timeframe!");
}

std::ostream& Schedule::serialize(std::ostream& os, const Schedule& val)
{
    if(!os) return os;

    os << val.name << '\n';

    for (int i = 0; i < val.SLOTS; i++)
    {
        if(!val.data[i])  os << "*";
        else{
            os << '|';
            val.data[i]->write(os, *val.data[i]);
            i += val.data[i]->get_length() - 1;
        }
    }

    return os;
}

std::istream& Schedule::deserialize(std::istream& is, Schedule& val)
{
    if(!is) return is;

    char* name = copy_from_stream(is, '\n');
    if(!name || is.get() != '\n') 
    {
        delete[] name;
        throw std::invalid_argument("Invalid file format!");
    }

    Task* temp[SLOTS]{};
    
    try
    {
        for (int i = 0; i < SLOTS; i++)
        {
            int symb = is.get();

            if(symb == '*')  continue;
            else if(symb == '|')
            {
                temp[i] = new Task(is);
                for(int j = 1; j < temp[i]->get_length(); ++j) temp[i + j] = temp[i];
                i += temp[i]->get_length() - 1;
            } 
            else throw std::invalid_argument("Invalid format!");
        }
    }
    catch(const std::exception& e)
    {
        for (int j = 0; j < SLOTS; j++) delete temp[j];
        delete[] temp;
        delete[] name;
        throw e;
    }

    val.free();
    val.name = name;
    for (int i = 0; i < SLOTS; i++)
    {
        val.data[i] = temp[i];
        temp[i] = nullptr;
    }

    return is;
}

bool Schedule::remove_task(const Task* task) {
    
    for (int i = 0; i < SLOTS; i++)
    {
        if(data[i] != task) continue;

        Task* t = data[i];
        for (int j = 0; j < t->get_length(); j++) 
        {
            data[i + j] = nullptr;
        }

        delete t;
        return true;
    }   

    return false;
}

void Schedule::free() noexcept {
    delete[] name; name = nullptr;
    for (int i = 0; i < SLOTS; i++) 
    {
        if(!data[i]) continue;

        Task* t = data[i];
        for (int j = 0; j < t->get_length(); j++) data[i + j] = nullptr;
        delete t;
    }
}

bool Schedule::set_name(const char* what) {
    if(!what) return false;

    char* temp = new(std::nothrow) char[strlen(what) + 1];
    if(!temp) return false;

    strcpy(temp, what);
    delete[] this->name;
    this->name = temp;

    return true;
}