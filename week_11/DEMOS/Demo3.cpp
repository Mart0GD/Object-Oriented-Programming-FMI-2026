#include <string.h>

class Base {
public:
    Base();
    virtual ~Base() = default; // Base има виртуална таблица 
};

class Der : public Base {
public:
    Der(const char* mem) : str(strcpy(new char[strlen(mem) + 1], mem )) {}
    virtual ~Der() override { delete[] str; }
private:
    char* str;
};

int main(void){
    Base* b = new Der("word");

    /* 
    * Kомпилаторът вижда, че деструктора е виртуален, прочитат се бървите 
    * 8 байта, които са адрса на таблицата и се извиква правилния деструктор 
    */

    delete b; 
}