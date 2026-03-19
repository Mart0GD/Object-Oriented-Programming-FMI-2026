#include <iostream>
#include <fstream>
#include "product.hpp"

int main(void){
    std::fstream os("My_bin.data", std::ios::in | std::ios::out | std::ios::trunc);
    if(!os.is_open()) return -1;


    data_init(os);
    add_product({"Pesho", 10, 25.45}, os);
    add_product({"Kofa", 10, 11.45}, os);
    add_product({"Kola", 4, 2.45}, os);
    delete_product(1, os);
    add_product({"neshto", 4, 10}, os);
    update_on_pn(1, 4, os);

    report(os);

    os.close();
    return 0;
}