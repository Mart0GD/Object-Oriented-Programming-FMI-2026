# Задача 1 – Статистика на текстов файл

В тази задача трябва да извличате статистическа информация от текстов файл, подобно на статистиката в текстов редактор като **Microsoft Word**.

---

## Структура за статистика

Дефинирайте следната структура:

~~~cpp
struct file_statistics {
    int total_symbols_count;            // общ брой символи
    int non_white_space_symbols_count;  // символи без whitespace
    int line_count;                     // общ брой редове
    int non_whitespace_lines_count;     // брой непразни редове
    int words_count;                    // брой думи
};
~~~

### Дефиниции:

Дума – последователност от символи с дължина ≥ 2.  
Разделител на думи – интервал (' ').  
Непразен символ – символ с ASCII код > 32 и < 127.  
Непразен ред – ред, който съдържа поне един непразен символ.  

### Имплементация:

Имплементирайте следните функции за извличане на статистика от файл.

## Функции за имплементация

Имплементирайте следните функции за извличане на статистика от файл.

как би форматирал тази задача 

## Задача 1

В тази задача от вас ще се изисква да извличате информация относно подаден текстови файл, подобно на тази в Word.   
  
За целта дефинирайте следната структура статистика: 

~~~.cpp
struct file_statistics {
    int total_symbols_count;
    int non_white_space_symbols_count;
    int line_count;
    int non_whitespace_lines_count;
    int words_count;
};
~~~

От вас ще се изисква да имплементирате следните функции, които ще служат за работа и манипулация на тази структура.

1.
~~~.cpp

~~~

~~~.cpp

//  Функция, която извлича броят на всички думи във файла. 
void extract_words(file_statistics& stats, std::ifstream& is);

// Функция, която извлича броят на всички символи във файла.
void extract_symbols(file_statistics& stats, std::ifstream& is);

// Функция, която извлича броят на всички непразни символи във файла.
// Непразен символ е всеки, чийто ASKII код е > 32 и < 127
void extract_non_whitespace_symbols(file_statistics& stats, std::ifstream& is);

// функция, която извлича броят на редовете във файла.
void extract_lines(file_statistics& stats, std::ifstream& is);

// Функция, която извлича, броят на непразните редове във файла.
void extract_lines(file_statistics& stats, std::ifstream& is);

// Функция, която принтира статистиката на конзолата подаден поток
void print_stats(const file_statistics& stats, std::ostream& os);
~~~
