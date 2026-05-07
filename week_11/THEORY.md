## Виртуални функции

Виртуалните функции в C++ са специален тип член функции на даден клас, които могат да имплементираме различна логика спрямо това, кой ги извиква. Те могат да бъдат единствено и само член функции, асоцирани към даден тип (клас). Като думичката **virtual** пишем в класа, който я декларира (дефинира) за първи път.

Ето един пример за това как можем да имаме няколко абсолютно еднакви по прототип член функции в различни разширения на даден клас, обаче те да не са виртуални. В този случай, имаме различна логика за всеки тип, но не можем да се възползваме от това по никакъв начин?

~~~.cpp
#include <iostream>
using namespace std;

class Bank_Account {
public:
    Bank_Account(float balance) : balance(balance){}; 
    void print_balance() { cout << "Cannot access balance in a non user profile!\n"; }
protected:
    float balance;
};

class Checking_Account : public Bank_Account {
public:
    Checking_Account(float balance) : Bank_Account(balance){};
    void print_balance() { cout << "Checking_Account balance is " << balance << '\n'; }
};

class Savings_Account : public Bank_Account {
public:
    Savings_Account(float balance) : Bank_Account(balance){};
    void print_balance() { cout << "Savings_Account balance is " << balance << '\n'; }
};

int main(){
    Bank_Account        b_a(0);
    Checking_Account    checking(100);
    Savings_Account     savings(1000);

    // Когато ги използваме асоцирани към своят си тип всичко е както очаквано?
    b_a.print_balance();            // --> Cannot access balance in a non user profile!
    checking.print_balance();       // --> Checking_Account balance is 100 
    savings.print_balance();        // --> Savings_Account balance is 1000

    // Нека се опитаме да ги унифицираме към базовият им клас
    Bank_Account* base_ptr1 = &checking;
    Bank_Account* base_ptr2 = &savings;

    // Тук очакваме отново да изпише същото, както горе, но това ли ще стане?
    base_ptr1->print_balance();     // --> Cannot access balance in a non user profile!
    base_ptr2->print_balance();     // --> Cannot access balance in a non user profile!
    
    return 0;
}
~~~

**Това е много добър пример за статично свързване на функции в C++.**

Нарича се статично, тъй като адресът на функцията е ясен на нашия компилатор по време на работата му. Той вижда, че **base_ptr1** е от тип **Bank_Accout**, затова директно при извикването на ``base_ptr1->print_balance();``, в генерираните **assembly** команди има поставен адрес на дефиницията на функцията в класа Bank_Account и нищо повече.



Преди да продължим напред, нека да припомним на какви сегменти се разделяше нашата програма:

| Сегмент | Съдържание | Кога се генерира | Права за достъп |
| :--- | :--- | :--- | :--- |
| **Code (Text)** | Машинните инструкции на функциите. | Compile-time | Read-Only / Execute |
| **Data (ROData)** | vtable, typeinfo, низови литерали, const променливи. | Compile-time | Read-Only |
| **Data (G/S)** | Глобални и статични променливи. | Compile-time | Read/Write |
| **Heap (Купчина)** | Динамична памет (new, malloc). | Runtime (в движение) | Read/Write |
| **Stack (Стек)** | Локални променливи, параметри на функции, адреси за връщане. | Runtime (в движение) | Read/Write |

Ето как изглеждат **много опростено** нашите класове в паметта:

~~~.cpp
                              |                      |          
                              |----------------------|                                      
                              |   float B_A::balance  |                                                    
                              |----------------------|     (Stack)                                       
                              |                      |                                                                                         
                        ------|----------------------|-------                                   
                              | B_A::print_balance() |     (Code Segment)
                              |----------------------|          

      |                        |                    |                        |
      |------------------------|                    |------------------------|
      |    float B_A::balance   |                    |    float B_A::balance   |
      |------------------------|                    |------------------------|
      |                        |                    |                        |
------|------------------------|--------------------|------------------------|------
      |   B_A::print_balance() |                    |   B_A::print_balance() |
      |------------------------|                    |------------------------|
      |   C_A::print_balance() |                    |   S_A::print_balance() |
      |------------------------|                    |------------------------|
          (Code Segment)                                  (Code Segment)
~~~



~~~.cpp
class Der : public Savings_Account{
    //...
};

int main(){
    Der d(1000);
    d.print_balance(); // --> Savings_Account balance is 1000
}
~~~

Проблемът става ясен, когато вземем указател от базов тип към наследника, тъй като получаваме единствено и само данните за базовият клас 


~~~.cpp
[ Vtable за Checking_Account ]          [ Typeinfo за Checking_Account ]
+----------------------------+         +-------------------------------+
| Offset to top (0)          |         | vtable for typeinfo_class     |
+----------------------------+         +-------------------------------+
| Pointer to Typeinfo  ----->|-------->| Name: "16Checking_Account"    |
+----------------------------+         +-------------------------------+
| Address of print_info()    |         | Pointer to Base Typeinfo      |
+----------------------------+         +-------------------------------+
| Address of other_virtual() |
+----------------------------+
~~~
