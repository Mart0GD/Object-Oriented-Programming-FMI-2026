#include "Task.hpp"
#include "string.h"
#include "helpers.hpp"

#include <limits>

Task::Task(const char* description, unsigned priority, unsigned length)
    : description(copy_string(description))
    , length(length)
    , completed(false)
{
    if(!set_priority(priority))
    {
        throw std::invalid_argument("Invalid priority level!");
    }
}

Task::Task(std::istream& is)
    : description(copy_from_stream(is))
{
    if(!is || !description || is.get() != DELIMITER)
    {
        delete[] description;
        throw std::invalid_argument("Invalid input file!");
    }

    is >> this->priority;
    if(!is || is.get() != DELIMITER)
    {
        delete[] description;
        throw std::invalid_argument("Invalid input file!");
    }

    is >> this->length;
    if(!is || is.get() != DELIMITER)
    {
        delete[] description;
        throw std::invalid_argument("Invalid input file!");
    }

    is >> this->completed;
    if(!is)
    {
        delete[] description;
        throw std::invalid_argument("Invalid input file!");
    }
}

Task::Task(const Task& other)
    : Task(other.description, other.priority, other.length) {  }

Task::~Task() noexcept
{
    delete[] description; description = nullptr;
}

void Task::finish() { completed = true; }

bool Task::set_priority(unsigned new_priority)
{
    if(new_priority > MAX_PRIORITY) return false;
    
    priority = new_priority;
    return true;
}

std::ostream& Task::write(std::ostream& os, const Task& val)
{
    if(!os) return os;

    os 
    << val.description  << DELIMITER 
    << val.priority     << DELIMITER 
    << val.length       << DELIMITER 
    << val.completed;

    return os;
}