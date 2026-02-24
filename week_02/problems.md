## Vector 3D

В тази задача от Вас ще се изисква да създадете малка библиотека за работа и манипулация на вектори в тримерното пространство. За целта създайте структура Vector3D с полета съответно **x**, **y**, **z**. Имплементирайте следната функционалност:

~~~.cpp

// Пресмята дължината на вектор
double length(const Vector3D& V);

// Пресмята скаларното произведение на два вектора
double dot_product(const Vector3D& V1, const Vector3D& V2);

// Пресмята векторното произведение на 2 вектора
Vector3D cross_product(const Vector3D& V1, const Vector3D& V2);

// Пресмята смесеното произведение на 3 вектора
double tripple_product(const Vector3D& V1, const Vector3D& V2, const Vector3D& V3);

// Умножава x, y, z на вектора по скалара
void multiply_by_scalar(Vector3D& V, double scalar);

// Нормализийра подаден вектор. (Един вектор е нормализиран, когато дължината му е 1)
void normalize(Vector3D& V);

// връща вектора с обратни стойности за всяка координата
Vector3D get_negative(const Vector3D& V);

// Намира сбора на два вектора
Vector3D sum(const Vector3D& V1, const Vector3D& V2);

// Намира разликата на два вектора
Vector3D diff(const Vector3D& V1, const Vector3D& V2);

// принтира вектора на конзолата във формат - (x,y,z)
void print(const Vector3D& v);
~~~

## Collision Components 

В тази задача от Вас се изисква да създадете статична collision система за чисто новият game engine на пазара **CantCountToThree**, на който ще направят новия Half Life 3. Gameplay департамента искат от вас възможност за работа с правоъгълни, триъгълни и кръгли collision компоненти, който да имат функционалността да отчитат дали се намират в сблъсък (дали са една върху друга). От вас се иска следното:  
  
Направете структура `Transform2D`.   
Тя ще пази - позиция и размер.    
   
Направете структура `TriangleCollisionComponent`.  
Това е компонента която ще представлява геометричната фигура триъгълник. Тя ще има като полета три върха.  
  
Направете структура `SquareCollisionComponent`.  
Това ще бъде геометричен квадрат. Пазете четирите му страни.  
  
Направете структура `CircleCollisionComponent`.  
Това ще бъде окръжност. Пазете центъра и радиуса й.  

Имплементирайте следната функционалност за работа със структурите:  

~~~.cpp

bool collides(const TriangleCollisionComponent& t, const SquareCollisionComponent& s);
bool collides(const TriangleCollisionComponent& t, const CircleCollisionComponent& s);
bool collides(const TriangleCollisionComponent& t, const TriangleCollisionComponent& s);

bool collides(const SquareCollisionComponent& t, const SquareCollisionComponent& s);
bool collides(const SquareCollisionComponent& t, const CircleCollisionComponent& s);
bool collides(const SquareCollisionComponent& t, const TriangleCollisionComponent& s);

bool collides(const CircleCollisionComponent& t, const SquareCollisionComponent& s);
bool collides(const CircleCollisionComponent& t, const CircleCollisionComponent& s);
bool collides(const CircleCollisionComponent& t, const TriangleCollisionComponent& s);


// Проверява дали дадена точка се намира в обекта (помислете как да представите точките?)
bool   is_inside(<параметри>);
double distance_between(const Transform2D& pos1, const Transform2D pos2);
// функции за прочитане от конзолата на всяка една от компонентите. Изберете сами как ще ги представите като вход

// !БОНУС!
// Създайте структура map, която ще пази всички инстнцирани обекти в нашата игра. Създайте следната функция, която сканира с окръжност около конкретна точка
// връща броят на обектите в тази област

// функция, която сканира area място около точката за обекти и връща броят им.
bool collision_check_area(const map& m, <точка>, int area); 
~~~

За всяка от фигурите считайте, че има Transfor2D и че размерът е лицето на фигурата.
Game Engine-а все още е много ранна и тайна фаза, затова все още няма истински движещи се обекти.

## Fruit Shop

Създайте структура, която ще моделира плод:  

~~~.cpp
struct Fruit
{
  char name[32]; // име на плод
  color cl;      // цвят на плод
  yn annual;     // едногодишен плод
  yn perennial;  // многогодишен плод
  yn tropical;   // тропически плод
};
~~~
  
**color** е изборен тип, като изберете сами какви и колко стойности да има.   
**yn** е изборен тип със стойности Yes и No.    

Напиште следните функции за работа с плодове:  

1) `Fruit* read_fruit()` - Прочита данните за n на брой плода от конзолата, записва ги в масив и връща резултата.  
2) void sort_fruit(Fruit* fruit) - Сортира по име, цвят и продължителност на плододаване плодовете, зададени чрез масива.  
3) Функция, която принитра плод на конзолата.  
4) `strange_print(color c)` - извежда многогодишните, тропически плодове с даден цвят, сортирани в низходящ ред по име на плода  

Демонстрирайте функциите в кратка програма, където прочитате масив от плодове от конзолата, сортирате ги и след това принтирате според (4).

## Event Handler

Напишете **Event Handler** система, която трябва да поддържа изпращането на пакети (event-и) между различните системи на вашето приложение. Като един event може да съдържа **ЕДНО** от следното:

- текст състоящ се от най-много 32 буквен текс.
- код на данни за прочит от конзолата (Един от: **Image**, **Message**)

---

Какво трябва да поддържа **Изображението**.

Матрица от стойности, както и тип - **bw** (black and white), **grayscale** и **colored**.
~~~.cpp
struct image{
    int* matrix;
    <some_enum> type;
};
~~~

При прочитане от конзолата на изображение първо четем типа му на първия ред и след това прочитаме самото изображение от другия ред надолу. Ако при четене установите, че изображение има заложен някакъв тип, но пикселите му не отговарят на описанието конвертирайте го към съответния тип. Важна подробност е, че bw е подмножество на grayscale, а grayscale е подмножество на colored. Като пример, ако ви се подаде черно бяла снимка от тип colored нищо не правите - bw е подмножество на colored, следователно е коректно.

След коректно прочитане на изображението от конзолата, принтирайте го.

--- 
Какво трябва да съдържа **Закриптирания текст**.

Символен низ и отстъп на криптирането.
~~~.cpp
struct encripted{
    char* text;
    int step;
};
~~~

Закриптиран текст четем във формата <step> <text>. Текстът е закриптиран чрез [шифърът на цезар](https://en.wikipedia.org/wiki/Caesar_cipher) със стъпка **step**. Прочетете текста, разшифровайте го и го принтирайте.

---

Ходът на програмата ще е следния. В началто на програмата започвате да четете event-и един по един от конзолата, докато не достигнем до команда END, тогава приключваме четенето и едина по една изпълняваме командите в event-ите. 

При код от тип **Image** или **Message**. Следваме написаното по-горе, за четене и изпълнение на такава команда. При низ, просто принтираме низа на конзолата.
