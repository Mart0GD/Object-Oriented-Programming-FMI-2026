#include <string.h>
#include <iostream>

using namespace std;

class Plant {
public:
    Plant(const char* family, const char* region)
        : region (strcpy(new char[strlen(region) + 1], region))
    {
        if(strlen(family) >= 64) throw std::invalid_argument("Invalid string!");
        strcpy(this->family, family);
    }

    Plant(const Plant& other) : Plant(other.family, other.region) {};
    Plant& operator = (const Plant& other)
    {
        if(this != &other)
        {
            char* temp = strcpy(new char[strlen(other.region) + 1], other.region);
            delete[] region;
            region = temp;
            strcpy(family, other.family);
        }

        return *this;
    }
    virtual ~Plant() noexcept { delete[] region; }

protected:
    char family[64];
    char* region;
};

class Vegetable : public virtual Plant{
public:
    Vegetable(const char* family, const char* region, int taste_factor, int meals_cnt)
        : Plant(family, region) 
        , taste_factor(taste_factor)
        , meals_cnt(meals_cnt) { }

    virtual ~Vegetable() noexcept override = default;

    virtual void eat() const { cout << "eating";} 

protected:
    int taste_factor;
    int meals_cnt;
};

enum Season {
    Spring,
    Summer,
    Fall,
    Winter
} season;

class SeasonalPlant : public virtual Plant {
public:
    SeasonalPlant(const char* family, const char* region, Season season)
        : Plant(family, region)
        , season(season) {}
    virtual ~SeasonalPlant() noexcept = default;

protected:
    Season season;
};

class Potato : public SeasonalPlant, public Vegetable {
public:
    Potato(const char* region, const char* family, float weight)
        : Plant(family, region)
        , SeasonalPlant(region, family, Summer)
        , Vegetable(region, family, 10, 1)
        , weight(weight) {}
    virtual ~Potato() noexcept override = default; 

    virtual void eat() const override { cout << "Eating Potato"; } 

protected:
    float weight;
};

class SweetPotato : public Potato {
public:
    SweetPotato(const char* region, const char* family, float weight, const char* cooking_book_id)
        : Plant(family, region)
        , Potato(region, family, weight)
        , cooking_book_id(copy_str(cooking_book_id)) 
        {
            if(!cooking_book_id) throw std::bad_alloc();
        };
    
    SweetPotato(const SweetPotato& other)
        : Plant(other)
        , Potato(other)
        , cooking_book_id(copy_str(other.cooking_book_id))
    {   
        if(!cooking_book_id) throw std::bad_alloc();
    }

    // Подаваме по копие с цел размяна 
    SweetPotato& operator = (SweetPotato other)
    {
        if(this != &other)
        {
            /*
            *   Вариант 1
            *   Тук силно нарушаваме полиморфизма, тъй като директно разменяме данните,
            *   но така гарантирам, че няма да има повторни копирания!
            */
            std::swap(static_cast<Plant&>(*this), static_cast<Plant&>(other));
            std::swap(this->meals_cnt, other.meals_cnt);
            std::swap(this->taste_factor, other.taste_factor);
            std::swap(this->season, other.season);
            std::swap(this->weight, other.weight);

            // Нашите данни
            std::swap(this->cooking_book_id, other.cooking_book_id);
        }

        return *this;
    }

    SweetPotato& operator = (const SweetPotato& other)
    {
        if(this != &other)
        {
            char* temp = new char[strlen(other.cooking_book_id) + 1];
            strcpy(temp, other.cooking_book_id);

            try
            {   
                /*
                *   Вариант 2
                *
                *   Това не е най-ефикасният вариант за жалост...
                *   Тъй като само конструкторите гарантират единствено извикване на базов такъв
                *   Операторът за присвояване тук ще копира данните и после пак в Potato и 
                *   така пак във Vegetable и SeasonalPlant
                */
                Plant::operator=(other);
                Potato::operator=(other);
            }
            catch(const std::exception& e)
            {
                delete[] temp;
                throw e;
            }

            delete[] cooking_book_id;
            cooking_book_id = temp;
        }

        return *this;
    }

    virtual ~SweetPotato() noexcept override { delete[] cooking_book_id; }

private:
    static char* copy_str(const char* str)
    {
        if(!str || *str == '\0') return nullptr;

        char* temp = new(std::nothrow) char[strlen(str) + 1];
        if(!temp) return nullptr;
        strcpy(temp, str);

        return temp;
    }

private:
    char* cooking_book_id;
};

int main(void) {
    Potato p("Europe", "Vegetabelus", 1.2);
    SeasonalPlant("Europe", "eeeee", Summer);
    return 0;
}