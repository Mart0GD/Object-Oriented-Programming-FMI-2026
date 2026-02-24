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

Направете структура `Transform2D`. Тя ще пази - позиция и размер.
Направете структура `TriangleCollisionComponent` - това е компонента която ще представлява геометричната фигура триъгълник. Тя ще има като полета три върха. 
Направете структура `SquareCollisionComponent` - това ще бъде геометричен квадрат. Пазете четирите му страни.
Направете структура `CircleCollisionComponent` - това ще бъде окръжност. Пазете центъра и радиуса й.

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

## Event Handler

Напишете Event Handler система, която трябва да поддържа изпращането на пакети (event-и) между различните системи на вашето приложение. Като един event може да 
съдържа следното:

- максимум 32 буквен текс.
- тип на данни, които да прочетем(*)
- код за грешка (помислете си как да го направите по-"елегантно")

(*) Типовете данни, които ще поддържаме са:

- Пакет с изображение.
- Закриптиран текс.

Пакетът е структура, която съдържа в себе си максимум изображение с големина 16x16, което трябва да се изобрази на екрана.
Закриптирания текс е последователност от символи, закодирана с шифъра на цезър с отстъп 3 символа.


