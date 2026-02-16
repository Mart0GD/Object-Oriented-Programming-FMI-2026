#include "iostream"

void change_my_number_to_two(int& number) {number = 2;}

void reallocate_array(int*& array, int new_size)
{
    int* temp = new(std::nothrow) int[new_size];
    if(!temp) return;

    for(int i = 0; i < new_size; ++i) temp[i] = array[i];

    delete[] array;
    array = temp;
}

int main()
{
    int a = 0;

    change_my_number_to_two(a);
    std::cout << a << std::endl;

    int* arr = new(std::nothrow) int[10];

    reallocate_array(arr, 20);

    arr[19] = 12;
    std::cout << arr[19] << std::endl;
    return 0;
}