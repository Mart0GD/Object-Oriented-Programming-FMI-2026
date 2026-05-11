#include <iostream>
using namespace std;

class Window_Closeable {
public:
    Window_Closeable(int value) : value(value) {};

    void execute() { cout << "close"; }
    inline int get_value() const { return value; }

    virtual void click_on() { cout << "Clicked Closeable window"; }

protected:
    int value;
};


class Window_Minimisable {
public:
    Window_Minimisable(int value) : value(value) {};

    void execute () { cout << "minimise"; }
    inline int get_value() const { return value; }

    void drag();
    virtual void click_on() { cout << "Clicked Minimisable window"; }

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

    virtual void click_on() override { cout << "Clicked on Custom window"; }

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

    // **Casting** 

    Window_Minimisable min = static_cast<Window_Minimisable>(window);
    Window_Closeable   min = static_cast<Window_Closeable>  (window);

    // **Virtual functions**
    Window_Minimisable* w_ptr1  = new Custom_Window(1024);
    Window_Closeable*   w_ptr2  = new Custom_Window(1024);
    Custom_Window*      w_ptr3  = new Custom_Window(1024);

    // Всички принтират "Clicked on Custom window"
    w_ptr1->click_on();
    w_ptr2->click_on();
    w_ptr3->click_on();
}