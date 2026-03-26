#include <cstring>

class Student {
private:
    char* name;
    int age;
    bool valid;

    void free() {
        delete[] name;
        name = nullptr;
    }

public:
    // Конструктор
    Student(const char* name, int age);

    // Деструктор
    ~Student() { free(); }

    inline const char*  getName() const { return name;}
    inline int          getAge()  const { return age; }


    bool setName(const char* newName);
    bool setAge(int newAge);
};