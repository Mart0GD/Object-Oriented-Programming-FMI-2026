
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <algorithm>

class Person{
public:
    Person() = default;
    explicit Person(int age, const char* name = "John Doe") : age(age) 
    {

        strcpy(this->name, name);
    };

    explicit Person(bool eyecolor, int age = 10, const char* name = "John does");

private:
    int age;
    bool eyecolor;
    char name[32];
};

class Car {
public:

    // Деструктор --> Копиращ Конструктор --> Оператора за присвояване 

    Car()
    : maker(nullptr)
    , model(nullptr)
    , passangers(nullptr)
    {}

    Car(const char* maker, const char* model, int year) 
        : year(year)
        , passangers(nullptr)
        , cnt(0)
    {
        this->maker = new char[strlen(maker) + 1];
        strcpy(this->maker, maker);

        this->model = new(std::nothrow) char[strlen(model) + 1];
        if(!this->model)
        {
            delete[] this->maker;
            throw std::bad_alloc();
        }

        strcpy(this->model, model);
    };

    Car(const Car& other)
        : Car(other.maker, other.model, other.year)
    {
        this->cnt = other.cnt;
        if(other.passangers == nullptr) return;

        this->passangers = new Person*[other.cnt]{};

        for (int i = 0; i < other.cnt; i++)
        {
            try
            {
                this->passangers[i] = new Person(*other.passangers[i]);
            }
            catch(...)
            {
                free();
                throw;
            }
        }
        
    }

    Car(Car&& other) 
        : model(other.model)
    {
        std::swap(model, other.model);
        std::swap(maker, other.maker);
        std::swap(passangers, other.passangers);

        this->cnt = other.cnt;
        this->year = other.year;
    }

    Car& operator = (Car&& other) 
    {
        std::swap(model, other.model);
        std::swap(maker, other.maker);
        std::swap(passangers, other.passangers);

        this->cnt = other.cnt;
        this->year = other.year;

        return *this;
    }


    Car& operator = (const Car& other)
    {
    //     free();

    //     this->maker = new char[strlen(other.maker) + 1];
    //     strcpy(this->maker, other.maker);

    //     this->model = new(std::nothrow) char[strlen(other.model) + 1];
    //     if(!this->model)
    //     {
    //         free();
    //         throw std::bad_alloc();
    //     }
    //     strcpy(this->model, other.model);

    //     try
    //     {
    //         this->passangers = new Person * [other.cnt]{};

    //         this->cnt = other.cnt;
    //         for (int i = 0; i < other.cnt; i++)
    //         {
    //             this->passangers[i] = new Person(*other.passangers[i]);
    //         }
    //     }
    //     catch(const std::exception& e)
    //     {
    //         free();
    //         throw;
    //     }

        char* maker_temp = new char[strlen(other.maker) + 1];
        strcpy(maker_temp, other.maker);

        char* model_temp = new(std::nothrow) char[strlen(other.model) + 1];
        if(!model_temp)
        {
            delete[] maker_temp;
            throw std::bad_alloc();
        }
        strcpy(model_temp, other.model);

        Person** passangers_temp = new(std::nothrow) Person*[other.cnt];
        if(!passangers_temp)
        {
            delete[] maker_temp;
            delete[] model_temp;

            throw std::bad_alloc();
        }


        for (int i = 0; i < other.cnt; i++)
        {
            passangers_temp[i] = new(std::nothrow) Person(*other.passangers[i]);
            if(!passangers)
            {
                delete[] maker_temp;
                delete[] model_temp;

                for (int hj = 0; hj < i; hj++)
                {
                    delete passangers[hj];
                }

                delete[] passangers_temp;
                throw std::bad_alloc();
            }
        }

        free();

        model = model_temp;
        maker = maker_temp;
        passangers = passangers_temp;
        cnt = other.cnt;
        
    
        Car c(other);
        *this = std::move(c);


        return *this;
    }

    ~Car()
    {
        free();
    }



private:

    void free()
    {
        delete[] maker;
        delete[] model;

        for(int i = 0; i < cnt; ++i)
        {
            delete passangers[i];
        }

        delete[] passangers;
    }

    const char* maker;
    char* model;

    int year;

    Person** passangers;
    int cnt;

};



void race(const Car& c)
{
    Car* cc = new Car(c);
    delete cc;
};


int main(void)
{
    try
    {
        Car c("Porsche", "911", 1988); 

        Car cc = c;

        Car ccc("Neshto", "Neshto", 10);

        ccc = cc;
        race(c);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    Person p = (int)1;

    return 0;
}
