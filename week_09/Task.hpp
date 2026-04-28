#pragma once

#include <iostream>

class Task{
public:

    Task(const char* description, unsigned priority, unsigned length);
    Task(std::istream& is);

    Task(const Task& other);
    Task& operator = (const Task& other) = delete;

    ~Task() noexcept;

    inline void             finish();
    bool                    set_priority(unsigned new_priority);
    
    static std::ostream&    write(std::ostream& os, const Task& val);

    inline unsigned         get_length()        const { return length; }
    inline unsigned         get_priority()      const { return priority; }
    inline const char*      get_description()   const { return description; }
    inline bool             finished()          const { return completed; }

private:

    const char* description;
    unsigned priority;

    bool completed;
    unsigned length;

    static const unsigned MAX_PRIORITY = 420;
    static const char     DELIMITER    = '|';
};