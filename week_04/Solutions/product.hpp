#pragma once

#include <assert.h>
#include <fstream>

static const int MAX_PRODUCTS = 100;

struct product {
    char description[32]; // 0
    int partition_number; // 32
    // 32 + 4 = 36 не се дели на 8. Има padding 4
    double cost;
};

static const int skip_distance_write = 40;
static const int skip_distance_read = 32;
static int products_cnt = 0;

void data_init(std::fstream& s);

void update_on_pn(double new_price, int p_n, std::fstream& s);

void update_on_field(double new_price, int p_n, std::fstream& s);

bool add_product(const product& p, std::fstream& s);

bool delete_product(int field, std::fstream&s);

void report(std::fstream& s);