## Множествено наследяване

В това упражнение ще се занимаваме с концепцията за **множествено наследяване** - нейните плюсове и минуси, как по точно е имплементирана в езика **C++** 

Нека започнем с това как изглеждаше един клас линейно в паметта:

~~~.cpp
struct A
{
    int  a;      // 4 bytes
    char symb;   // 1 byte
                 // 3 bytes padding
};

Разпределение в паметта:
+-------------------+
| int a        (4B) |
+-------------------+
| char symb    (1B) |
+-------------------+
| padding      (3B) |
+-------------------+

Общ размер: 8 bytes
~~~

Нека сега разгледаме паметта на два обекта в наследяваща йерархия:

~~~.cpp
struct A
{
    int  a;        // 4B
    char symb;     // 1B
                   // 3B padding
};                 // sizeof(A) = 8B

struct B : A
{
    float val;     // 4B
    char arr[12];  // 12B
};                 // sizeof(B) = 24B


Разпределение в паметта на B:
+---------------------------+
| A::a                (4B)  |
+---------------------------+
| A::symb             (1B)  |
+---------------------------+
| padding             (3B)  |
+---------------------------+
| float val           (4B)  |
+---------------------------+
| char arr[12]       (12B)  |
+---------------------------+

Общ размер: 24 bytes
~~~

Така както виждате, разпределението на памет винаги е от базовия клас към наследника, като наследника пази всичката информация и за базовият си клас, точно по този начин обръщения като ``obj_b.symb`` са възможни.  

Нека обаче разширим нашият поглед и направим класът **B** да наследява още един базов клас. 

~~~.cpp
struct A1
{
    int  a;        // 4B
    char symb;     // 1B
                   // 3B padding

    void do()      { ... }
};                 // sizeof(A1) = 8B


struct A2
{
    int a;         // 4B

    void do()      { ... }
};                 // sizeof(A2) = 4B


struct B : A1, A2
{
    float val;     // 4B
    char arr[12];  // 12B
};


Разпределение в паметта на B:
+----------------------------------+
| A1::a                     (4B)   |
+----------------------------------+
| A1::symb                  (1B)   |
+----------------------------------+
| padding                   (3B)   |
+----------------------------------+
| A2::a                     (4B)   |
+----------------------------------+
| B::val                    (4B)   |
+----------------------------------+
| B::arr[12]               (12B)   |
+----------------------------------+

Общ размер:
8 + 4 + 4 + 12 = 28B
~~~

Тук вече се вижда един сериозен проблем, имаме припокриващи се данни и се получават така наречените неопределимости. Какво ще стане когато поискаме стойността ``a`` от обект с тип **B** или пък какво става ако поискаме да извикаме функция споделена между двата типа? 

Със следващият пример ще отговоря на тези въпроси, генерално имаме два подхода в зависимост от това как очакваме нашите обекти да се държат

~~~.cpp
#include <iostream>
using namespace std;

class Window_Closeable {
public:
    Window_Closeable(int value) : value(value) {};

    void execute() { cout << "close"; }
    inline int get_value() const { return value; }

protected:
    int value;
};


class Window_Minimisable {
public:
    Window_Minimisable(int value) : value(value) {};

    void execute () { cout << "minimise"; }
    inline int get_value() const { return value; }

    void drag();

protected:
    int value;
};

class Custom_Window : public Window_Minimisable, public Window_Closeable {
public:
    Custom_Window(int value) : Window_Minimisable(value), Window_Closeable(value) {};

    inline int get_color() const { return color; }

    // 2. Начин за решаване
    // inline int get_value() const { return Window_Closeable::get_value();}

    void update_pixels() 
    {
        // Пак проблем, докато имената (логиката) се припокриват няма да се измъкнем 
        // int size = value;

        int size = Window_Closeable::value;
        for(int i = 0; i < size; ++i)
        {
            // update ...
        }
    }

private:
    int color;
};

int main(){
    Custom_Window window(1024);

    // Проблем, имам две такива за всеки клас. Кое да избере?
    // window.execute();
    // window.get_value(); 

    // Има два начина за решение на проблема 

    // 1. Специфициране експлицитно кое да се извика!
    window.Window_Minimisable::get_value();
    window.Window_Closeable::get_value();
    
    // 2. Напишете си собствена функция
    // window.get_value();
}
~~~  
  
Това, което разгледахме в момента е единствено и само проблем при променливи/функции със споделени имена. Нищо не ни спира да извикаме функция от кой да е от базовите класове, която не е в случай на неопределимост, даже не плащаме и цена за това, защото компилатора просто оказва оширение (offset) от началото на сегмента ни с код до желаната функция!

~~~.cpp
    Custom_Window window(1024);
    window.drag(); // никакъв проблем 
~~~  
  
**Преобразуване**

Преобразуването (**Casting**) е интуитивно, можем да преобразуваме нашият обект, както към единия така и към другия базов клас без проблеми, просто указателят/паметта за новият обект ще е отместена.

~~~.cpp
    Window_Minimisable min = static_cast<Window_Minimisable>(window);
    Window_Closeable   min = static_cast<Window_Closeable>  (window);
~~~

**Виртуални фунцкии**

Виртуалните функции в случая работят както очакваме, всеки наследник клас може да имплементира виртуални функции от базовите си класове както си поиска, като виртуалната му таблица се обновява с негобите дефиниции или тези, които са били в базовия.

~~~.cpp
class Window_Closeable {
    // ...
    virtual void click_on() { cout << "Clicked Closeable window"; }
};

class Window_Minimisable{
    // ...
    virtual void click_on() { cout << "Clicked Minimisable window"; }
};

class Custom_Window : public Window_Minimisable, public Window_Closeable {
    // ...
    virtual void click_on() override { cout << "Clicked on Custom window"; }
};

int main() {
    Window_Minimisable* w_ptr1  = new Custom_Window(1024);
    Window_Closeable*   w_ptr2  = new Custom_Window(1024);
    Custom_Window*      w_ptr3  = new Custom_Window(1024);

    // Всички принтират "Clicked on Custom window"
    w_ptr1->click_on();
    w_ptr2->click_on();
    w_ptr3->click_on();
};
~~~

**Виртуални таблици**

При множествено наследяване, когато се дефинират виртуални функции в базовите класове, нашият клас наследник трябва да дефинира **виртуални таблици** за всеки базов клас. Това се случва с цел, да можем да **преобразуваме** обект от типа на наследника към кой да е базов тип, без да загубим каквато и да е информация.

Ето как изглежда паметта за нашият обект **Custom_Window**

~~~.cpp
                      Custom_Window 
┌───────────────────────────────────────────────────────┐
│                                                       │
│  Window_Minimisable                                   │
│  ┌───────────────────────────────────────────────┐    │
│  │ vptr_Minimisable  ───────────────┐            │    │
│  │ int value                        │            │    │
│  └──────────────────────────────────┘            │    │
│                                                  │    │
│  Window_Closeable                                │    │
│  ┌──────────────────────────────────────────┐    │    │
│  │ vptr_Closeable  ───────────────────┐     │    │    │
│  │ int value                          │     │    │    │
│  └────────────────────────────────────┘     │    │    │
│                                             │    │    │
│    int color                                │    │    │
│                                             │    │    │
└─────────────────────────────────────────────┘    │    │
                                                   │    │
                                                   │    │
        таблица за Custom_Window                   │    │
        като Window_Minimisable                    │    │
        ┌───────────────────────────────┐          │    │
        │ &Custom_Window::click_on      │◄─────────┘    │
        └───────────────────────────────┘               │
                                                        │
                                                        │
        таблица за Custom_Window                        │
        като Window_Closeable                           │
        ┌───────────────────────────────┐               │
        │ &Custom_Window::click_on      │◄──────────────┘
        └───────────────────────────────┘
~~~

## Диамантено наследяване

Нека разгледаме следната йерахия от класове

~~~.cpp
#include <iostream>
using namespace std;

struct Person {
    Person(int age) : age(age) {};

    int age;
    void foo() { cout << "I am a Person"; }
};

struct Teacher : public Person {
    Teacher(int age, int years_of_teaching)
        : Person(age), years_of_teaching(years_of_teaching) {};

    int years_of_teaching;
};

struct Pilot : public  Person {
    Pilot(int age, int flight_hours)
        : Person(age), flight_hours(flight_hours) {};

    int flight_hours;
};

struct Flight_Instructor : public Teacher , public Pilot {
    Flight_Instructor(int age, int flight_hours, int years_of_teaching, float hour_rate)
        : Teacher(age, years_of_teaching), Pilot(age, flight_hours), hour_rate(hour_rate) {};

    float hour_rate;
};
~~~

Тук се срещаме с наследяване тип диамант, тъй като в случая **Flight_Instructor** наследява експлицитно **Teacher** и **Pilot**, но наследява **Person имплицитно** два пъти. Това може да поради добро или както в повечето **случай** лошо архитектурно решение...

В източници онлайн ще видите този пример описан като **диамантен проблем** или **the diamond of despair**, но обаче не винаги е проблем. Тук много добре искаме инструктора по пилотиране да бъде както пилот така и учител, в това няма проблем.   

Ето с какво трябва да внимаваме при работа с обекти от тип **Flight_Instructor**

~~~.cpp
int main(void){
    Flight_Instructor* pesho = new Flight_Instructor{10, 100, 4, 45};

    // Валидно
    Pilot* pilot_pesho      = static_cast<Pilot*>(pesho);
    Teacher* teacher_pesho  = static_cast<Teacher*>(pesho);

    // Невалидно --> коя част от Person да вземе, като пилот или като учител?
    // Person* person_pesho1    = static_cast<Person*>(pesho);

    // Така вече е валидно 
    Person* person_pesho     = static_cast<Person*>(static_cast<Teacher*>(pesho));

    // Сега обратното пак е невалидно
    // Flight_Instructor* pesho_back = static_cast<Flight_Instructor*>(person_pesho);

    // Но можем да вземем обратно учителската част 
    Flight_Instructor* pesho_back = static_cast<Flight_Instructor*>(static_cast<Teacher*>(pesho_back));

    return 0;
}
~~~

Ето това е диаграмата за това, как изглежда паметта на класа **Flight_Instructor**

~~~.cpp
Flight_Instructor : Teacher, Pilot
┌──────────────────────────────────────┐
│ Teacher subobject                    │
│ ┌──────────────────────────────────┐ │
│ │ Person subobject                 │ │
│ │ ┌────────────────────────────┐   │ │
│ │ │ int age                    │   │ │
│ │ └────────────────────────────┘   │ │
│ │                                  │ │
│ │ int years_of_teaching            │ │
│ └──────────────────────────────────┘ │
│                                      │
│ Pilot subobject                      │
│ ┌──────────────────────────────────┐ │
│ │ Person subobject                 │ │
│ │ ┌────────────────────────────┐   │ │
│ │ │ int age                    │   │ │
│ │ └────────────────────────────┘   │ │
│ │                                  │ │
│ │ int flight_hours                  │ │
│ └──────────────────────────────────┘ │
│                                      │
│ float hour_rate                       │
└──────────────────────────────────────┘
~~~

## Виртуално наследяване

В повечето случай, когато имаме диамантено наследяване ще искаме базовият клас да е споделен или по-точно един единствен в паметта, тъй като имаме две различни инстанции на базовия клас, те често се оказват проблем за нашата логика. Поради такива случаи в C++ е добавена логика за виртуално наследяване, която сега ще разгледаме.

Логиката е следната

~~~.cpp
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
    ~Plant() noexcept { delete[] region; }

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

protected:
    Season season;
};

class Potato : public SeasonalPlant, public Vegetable {
public:
    Potato(const char* region, const char* family, float weight)
        : Plant(region, family)
        , SeasonalPlant(region, family, Summer)
        , Vegetable(region, family, 10, 1)
        , weight(weight) {}

    virtual void eat() const override { cout << "Eating Potato"; } 

private:
    float weight;
};
~~~

В този пример се случват много неща. Ще ги разгледаме едно по едно, за да изясним бавно какво точно извършва думичката ``virtual``. 

---

**Виртуална таблица**

За обект от тип **Potato** се заделят три указателя за виртуални таблици, един за **SeasonalPlant** частта, друг за **Vegetable** и още един за базовата част от тип **Plant**. Ето какво точно се случва в най-долния ни клас от наследяването.

~~~.cpp
// Генерирано от GCC чрез Compiler Explorer 
"vtable for Potato":
        // Информация за SeasonalPlant
        .quad   40 --> колко байта има до базовия виртуален клас 
        .quad   0  --> колко далеч от началото на паметта се намира указателя на таблицата 

        // Информация за класа Potato
        .quad   "typeinfo for Potato"
        .quad   "Potato::eat() const"  // презаписаната виртуална фунцкия

        
        .quad   24  --> колко байта има до базовия виртуален клас 
        .quad   -16 --> колко далеч от началото на паметта се намира указателя на таблицата

        .quad   "typeinfo for Potato"
        .quad   "non-virtual thunk to Potato::eat() const"
~~~

Забележете, че при виртуално наследяване паметта на базовия клас се намира накрая на неговия блок памет, това улеснява много нещата с преобразуването от един клас към друг, тъй като базата винаги е накрая и винаги ще се включи!

Второто, което се случва е, че се налага да извикаме параметризирания конструктор на базовия клас, това е нужно, за да създадем **ЕДНА** единствена версия в паметта, която ще стои накрая на блока от памет за **Potato**. Конструкторът на **Plant** ще се извика винаги **първи** ако не го напишете изрично ще се извика този по **подразбиране**, запомнето това много добре! Ако имате забранени конструктори на базовия ще получите грешка...

Как конструкторите на **SeasonalPlant** и **Vegetable** знаят да не извикат базовия конструктор най-вероятно сега се питате и имате право. Това отново се случва благодарение на трудолюбивият ни компилатор, той създава две различни версии на конструкторите на класове, които имат думата virtual при наследяване. Като едната версия прави повикване към базовия си клас с подадените аргументи, а другата не. Тези две версии се избират предварително от компилатора, по време на компилация в зависимост от това какъв обект създаваме

Има и друг вариант на проверка. Той представлява подаване на 1-ца в конкретен регистър и вмъкване на if/else проверка в конструкторите на междинните класове с цел runtime пропускане на извикването на базовия клас, но по това което намерих тази опция е по-рядка и става за сложни конструктори, тъй като проверките за истина/лъжа са бавни! 

**Жизнен Цикъл**

Много важна подробност относно жизненият цикъл на виртуално наследен обект е, че операторите за присовяване **НЕ** гарантират единствено изпълнение, което означава, че при не добре написан оператор за присвояване можем да натрупаме множество копирания на данни в базовия клас **Plant**, без дори да се усетим. 

Ето как можем по няколко начина да постигнем работещ ефект.

~~~.cpp
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
~~~

---

[Източник] (https://www.usenix.org/legacy/publications/compsystems/1989/fall_stroustrup.pdf)
