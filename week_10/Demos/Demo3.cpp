
struct A {
    int a;
    int b;
};

struct B : public A {
    int c;
};

int main(){
    B first = {1,2,3};
    A copy = (A)first; // Вземаме само първите 8 байта от first
}