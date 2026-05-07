#include <iostream>
using namespace std;

class Bank_Account {
public:
    Bank_Account(float balance) : balance(balance){}; 
    virtual void print_balance() { cout << "Cannot access balance in a non user profile!\n"; }
protected:
    float balance;
};

class Checking_Account : public Bank_Account {
public:
    Checking_Account(float balance) : Bank_Account(balance){};
    virtual void print_balance() override { cout << "Checking_Account balance is " << balance << '\n'; }
};

class Savings_Account : public Bank_Account {
public:
    Savings_Account(float balance) : Bank_Account(balance){};
    virtual void print_balance() override { cout << "Savings_Account balance is " << balance << '\n'; }
};

int main(){
    Bank_Account        b_a(0);
    Checking_Account    checking(100);
    Savings_Account     savings(1000);

    // Това ще е абсолютно същото
    b_a.print_balance();            // --> Cannot access balance in a non user profile!
    checking.print_balance();       // --> Checking_Account balance is 100 
    savings.print_balance();        // --> Savings_Account balance is 1000

    // Но тук ще видим същинска промяна!
    Bank_Account* base_ptr1 = &checking;
    Bank_Account* base_ptr2 = &savings;

    // Като с някаква магия, функциите ни работят както сме ги дефинирали?
    base_ptr1->print_balance();     // --> Checking_Account balance is 100 
    base_ptr2->print_balance();     // --> Savings_Account balance is 1000

    // Същото важи и за референции
    Bank_Account& base_ref1 = checking;
    Bank_Account& base_ref2 = savings;

    base_ptr1->print_balance();     // --> Checking_Account balance is 100 
    base_ptr2->print_balance();     // --> Savings_Account balance is 1000
    
    return 0;
}