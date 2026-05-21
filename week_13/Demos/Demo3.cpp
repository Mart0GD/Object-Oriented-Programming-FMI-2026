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