#include <iostream>

int avg(int arr[], int size)
{
    int sum = 0;                 
    for(int i = 0; i < size; ++i)
    {                            
        sum += arr[i];           
    }                            
    return sum / size;           
}

#define max(a,b) ((a) > (b) ? (a) : (b))

#define get_average(arr, size) (                \
{                                               \
    int return_val;                             \
    return_val = avg(arr, size);                \
    return_val;                                 \
})

#define DONT_CRASH

#ifndef DONT_CRASH 
    #error("Crash...");
#endif

#ifdef DONT_CRASH
#else 
    #error("Crash...");
#endif

int main(void)
{   
    int arr[] = {1,2,3,4,5};

    int a = get_average(arr, 5);
    std::cout << a;

    return 0;
}