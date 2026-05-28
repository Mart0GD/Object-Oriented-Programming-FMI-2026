
#include <vector>
#include <iostream>

int main(){

    std::vector<int> arr;

    arr.push_back(1);
    arr.push_back(1);
    arr.push_back(1);
    arr.push_back(1);

    std::vector<int>::iterator itt = arr.begin();
    std::begin(arr);
    for (int el : arr)
    {
        std::cout << *itt << '\n';
    }
    
}