## Използване на шаблони

Шаблоните, както вече знаем са специални типове, които генерират типове или функции по време на компилация, спрямо това с какви аргументи сме ги използвали. С тяхна помощ постигахме така наречения статичен полиморфизъм!

Шаблони дефинирахме с помощта на следните две ключови думи (няма значение коя използвате):

``template<typename T>``

``template<class T>``

Ето пример за проста шаблонна функция с два аргумента:

~~~.cpp
template<typename T>
T min(const T& a, const T& b){
    return a < b ? a : b;
};
~~~

Това е нетипизирана функция, очакваща шаблонен параметър на име **T** (можете да го кръстите както си поискате). В момента, в който напишем ``template<>`` оказваме на компилатора, че каквато и конструкция да следва, тя ще очаква някакъв типов параметър предшестван от клюовите думи споменати по-горе!  

**Експлицитно vs Имплицитно извикване**

Използването на тази шаблонна функция става по два начина - явно чрез експлицитно оказване на аргументите или неявно чрез просто подаване на аргументи и оставяне на компилатора сам да прецени, спрямо някакви правила зададени в него:

~~~.cpp
int main(void){
    int a = 5;
    int b = 10;

    int less = min<int>(a,b;  // експлицитен начин
    int less = min(a,b);      // имплицитен начин

    return 0;    
};
~~~

При извикване на функцията за първи път с тип ``int`` в **translation unit-a** на кода се добавя чисто нова дефиния на шаблонната функция с **int** навсякъде, където е пишело **T**.

Понякога имплицитното ивикване не дава очакваните резултати, затова внимавайте как и какво подавате:

~~~.cpp
int main(void){
    int res1 = min<int>(4.2,4);
    int res2 = min<double>('b', 18.6121);
    int res3 = min(11, 14.3); // --> грешка, не може да се определи типа!
    return 0;
};
~~~

## Шаблонни параметри 

**Типови параметри**

Типовите параметри са тези с вид: ``typename <name>``, които до сега използвахме, типът може да бъде абсолютно всякакъв и броят на тези параметри е неограничен.

Ето пример за шаблонен клас с няколко типови параметъра:

~~~.cpp
template<typename Clan, typename Period, typename Class> class Warrior; 
~~~

Ако искате да дефинирате тип с неограничен брой шаблонни праметри, може да използвате оператора ellipsis (многоточие), като как да ги извлечете в последствие, може да прочетете сами.

~~~.cpp
template<typename A, typename B, ...> class My_Special_Class;

My_Special_Class<> a;           // без аргументи
My_Special_Class<int, bool> b;  // два аргуемнта
~~~

**Рестрикции спрямо аргументите**

В общия случай, ваш дефиниран шаблонен тип може да приеме какъвто и да е типов аргумент, освен ако за него не се изисква предварително дефинирана логика. Да се върнем на примера с фунцкията ``min``, която имаше един шаблонен параметър и сравняваше два обекта от подадения тип. Какво ще стане ако сравним два обекта от моя специален, несравним клас.

~~~.cpp
class Custom {
public:
    Custom(int data) : data(data){}:
private:
    int data;
};

int main(void){
    Custom a(10);
    Custom b(25);

    Custom res = min<Custom>(a, b); // грешка, типът не дефинира оператор < !!
    return 0;
};
~~~

Това е типична клопка, в която може да попаднем при използването на шаблони. 

Друг пример от стандартната библиотека с ``std::vector``, той не изисква обектите да имат конструктор по подразбиране (**защо?**), но изисква да могат да бъдат копирани и да имат оператор за присвояване.

**Нетипизирани параметри**

Това са параметри с някаква целочислна, стойност, които може да се подават допълнително на нашите типове. 

Ето няколко пример за тяхното използване:

~~~.cpp
template<typename T, size_t size>
class Array {...};

template<typename T, void (*f_ptr)> Functor;
~~~

Като допълнение вмъквам, че съществуват и типове с нетипови параметри дефинирани с **auto**, които могат да се определят от компилатора:

~~~.cpp
template<auto x> constexpr auto constant_type = x;

auto v1 = constant_type<25>;
auto v2 = constant_type<true>;
~~~

**Шаблонни параметри**

Като параметър можем да добавим и друг шаблонен тип, което рядко ще ни се наложи, но е добре да знаем, че можем да го направим ако ни потрябва!

~~~.cpp
template<typename T, template<typename S, size_t> class Arr>
class A{
public:
    ...
private:
    Arr<int,10> arr;
    T data;
    // S other_data;  --> до това нямаме достъп 
};
~~~

**Параметри по подразбиране**

Както типовите, така и нетиповите параметри могат да имат зададени стойности по подразбиране, като естествено следваме правилото всеки аргумент със стойност по подразбиране да бъде в края на параметрите.

~~~.cpp
template <class T, class Allocator = allocator<T>> class vector;
template <class T, size_t = 10> class Array;
//...
int main(void){
    vector<int, My_Custom_Allocator> my_vec1;
    vector<int>                      my_vec2;

    Array<int>    my_arr1;
    Array<int,20> my_arr2;
};
~~~

## Шаблонни класове

Когато пишем шаблонен клас имам два варианта за дефиниране на неговите член функции. Или ги дефинираме на място или ги дефинираме извън класа, като тогава трябва да изпишем цялата и дефиниция като шаблонна функция.

> Не забравяйте, пишем шаблонни функции или директно в header файла, или в специален файл .inl и т.н, който добавяме в header файла. Не пишем дефиниции в .cpp никога!!!

Ето как го правим:

~~~.cpp
template<typename T, int size>
class Stack {
public:
    Stack() {
        // вътрешна дефиниция, не пишем нищо допълнително...
    };

    void push(const T& item);
    T& pop();

private:
    T*     head;
    T      data[i];
    size_t cnt;
};

template< class T, int i > void Stack< T, i >::push(const T& item ) { // външна дефиниция... }

template< class T, int i > T& Stack< T, i >::pop() { // външна дефиниция... }
~~~

**Вложени шаблонни класове**

Това са член типове на класове както всички други, с единствената разлика, че са шаблонни. Дефиницията на класа може да е както вътре в класа така и извън класа, като при второто внимаваме, тъй като трябва да добавим две шаблонни дефиниции...

~~~.cpp
template<typename T>
class A {
    // ...
private:
    template<typename S>
    class B{
    public:
        B();
        S get_data() const { return data; }
    private:
        S data;
    };

    T data;
};

template<typename T>
template<typename S>
A<T>::B<S>::B() {
    // logic...
}
~~~

## Специализация

Специализациите са начин да додефинираме специална логика за нашите шаблонни типове ако те разползагат с множество параметри и за някои от тях е възможна по-специална и оптимизирана логика или ако имаме единствен тип, който има нужда от специална логика за обработка на указатели и референции. Ще се занимаваме повече с втория вариант.

Ето за специализация на шаблонен контейнер за работа с указатели:

~~~.cpp
#include <iostream>
using namespace std;

template <class T> 
class Bag {
   T* elem;
   int size;
   int max_size;

public:
   Bag() : elem(0), size(0), max_size(1) {}
    void add(T t) {
        if (size + 1 >= max_size) {
            T* tmp;
            max_size *= 2;

            tmp = new T [max_size];
            for (int i = 0; i < size; i++)
               tmp[i] = elem[i];

            try { tmp[size] = t;}
            catch(std:: exception& e) { delete[] tmp; throw e;}

            ++size;
            delete[] elem;
            elem = tmp;
        }
        else
            elem[size++] = t;
   }

   void print() {
      for (int i = 0; i < size; i++)
         cout << elem[i] << " ";
      cout << endl;
   }
};

// Специализация за указатели
template <class T> class Bag<T*> {
   T* elem;
   int size;
   int max_size;

public:
   Bag() : elem(0), size(0), max_size(1) {}
   void add(T* t) {
      if (t == nullptr) {   
         cout << "Null pointer!" << endl;
         return;
      }

      if (size + 1 >= max_size) {
            T* tmp;
            max_size *= 2;

            tmp = new T [max_size];
            for (int i = 0; i < size; i++)
               tmp[i] = elem[i];

            try { tmp[size] = *t;} // deref... 
            catch(std:: exception& e) { delete[] tmp; throw e;}

            ++size;
            delete[] elem;
            elem = tmp;
        }
        else
            elem[size++] = *t; // deref... 
   }

   void print() {
      for (int i = 0; i < size; i++)
         cout << elem[i] << " ";
      cout << endl;
   }
};

int main() {
   Bag<int> xi;
   Bag<char> xc;
   Bag<int*> xp; // използваме специализация...

   xi.add(10);
   xi.add(9);
   xi.add(8);
   xi.print();

   xc.add('a');
   xc.add('b');
   xc.add('c');
   xc.print();

   int i = 3, j = 87, *p = new int[2];
   *p = 8;
   *(p + 1) = 100;
   xp.add(&i);
   xp.add(&j);
   xp.add(p);
   xp.add(p + 1);
   delete[] p;
   p = NULL;
   xp.add(p);
   xp.print();
}
~~~
