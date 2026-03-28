class Circle{
public:

    // Конструктор по подразбиране, без инициализация на член данни
    Circle() {}

    // Конструктор само с 2 аргумента, извършва се специална логика
    Circle(int radius, int point)
    {
        this->radius = radius;
        this->center_x = this->center_y = point;
    }

    // конструктор, приемащ всички аргументи, които му трябват 
    Circle(int radius, int c_x, int c_y)
    {
        this->radius = radius;
        this->center_x = c_x;
        this->center_y = c_y;
    }

    int diameter() const { return radius * 2; }

// Стойностите ни вече са скрити от външния свят
private:
    int radius;
    int center_x;
    int center_y;
};