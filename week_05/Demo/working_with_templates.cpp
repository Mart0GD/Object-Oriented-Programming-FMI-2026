#include "working_with_templates.hpp"

void plus_one(int& el) { ++el; }

int main(void){

    int a = 0;
    add<int,int>(a,2.2f);   // неявно cast-ване към int
    add(a,10);              // може да се пропуснат темплейтните параметри 

    pow2<int>(a);
    add_to_number<int, 100>(a);

    int arr[3] = {0,0,0};
    apply_on_array<int, plus_one>(arr, 3);

    return 0;
}