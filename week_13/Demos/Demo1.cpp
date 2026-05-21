
template<typename T>
T min(const T& a, const T& b){
    return a < b ? a : b;
}

int main(){

    int res1 = min<int>(1,2);
    int res2 = min(1,2);
    int res3 = min<double>(2,2.4);
    int res4 = min<int>('b', 23.411);
    // int res5 = min('c', 45.4); --> грешка
}