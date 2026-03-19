#include "product.hpp"

void data_init(std::fstream& s)
{
    products_cnt = 0;

    s.clear();
    s.seekp(0);

    product dummy;

    for (int i = 0; i < MAX_PRODUCTS; i++)
    {
        s.write(reinterpret_cast<const char*>(&dummy), sizeof(product));
    }

}

void update_on_pn(double new_price, int p_n, std::fstream& s)
{
    assert(s);

    // Може да се напави и двоично търсене...
    
    if(products_cnt == 0) return;

    s.seekg(0);
    s.seekp(0);

    for (int i = 0; i < products_cnt; ++i)
    {
        if(i > p_n) break;

        int current_p_n;
        s.seekg((sizeof(product) * i) + skip_distance_read, std::ios::beg);
        s.read(reinterpret_cast<char*>(&current_p_n), sizeof(int));

        if(p_n == current_p_n)
        {
            s.seekp((i * sizeof(product)) + skip_distance_write, std::ios::beg);
            s.write(reinterpret_cast<const char*>(&new_price), sizeof(double));
        }
    }
    
}

void report(std::fstream& s)
{
    assert(s);
    if(products_cnt == 0) return;

    std::ofstream os("Result.txt");
    if(!os.is_open()) return;

    s.clear();
    s.seekg(0);
    for (int i = 0; i < products_cnt; i++)
    {
        product p;
        s.read(reinterpret_cast<char*>(&p), sizeof(product));
        os << p.description << ' ' << p.partition_number << ' ' << p.cost << '\n';
    }
}

void update_on_field(double new_price, int field, std::fstream& s)
{
    assert(s);
    if(field >= products_cnt) return;

    s.seekp(field * sizeof(product) + skip_distance_write);
    s.write(reinterpret_cast<const char*>(&new_price), sizeof(double));
}

bool add_product(const product& p, std::fstream& s)
{
    assert(s);
    if(products_cnt == MAX_PRODUCTS) return false;

    s.seekg(0); s.seekp(0);

    int pos = 0;
    for (; pos < products_cnt; ++pos)
    {
        int current_p_n;
        s.seekg(pos * sizeof(product) + skip_distance_read, std::ios::beg);
        s.read(reinterpret_cast<char*>(&current_p_n), sizeof(int));

        if(p.partition_number < current_p_n) break;
    }

    for (int i = products_cnt; i > pos; --i)
    {
        product temp;

        s.seekg((i - 1) * sizeof(product), std::ios::beg);
        s.read(reinterpret_cast<char*>(&temp), sizeof(product));

        s.seekp(i * sizeof(product), std::ios::beg);
        s.write(reinterpret_cast<char*>(&temp), sizeof(product));
    }

    s.seekp(pos * sizeof(product), std::ios::beg);
    s.write(reinterpret_cast<const char*>(&p), sizeof(product));
    ++products_cnt;
    s.flush();

    return true;
}

bool delete_product(int field, std::fstream&s)
{
    assert(s);
    if(field >= products_cnt) return false;

    for (int i = field; i < products_cnt - 1; ++i)
    {
        product dummy;
        s.seekg((i + 1) * sizeof(product), std::ios::beg);
        s.read(reinterpret_cast<char*>(&dummy), sizeof(product));
        if(!s) return false;

        s.seekp(i * sizeof(product), std::ios::beg);
        s.write(reinterpret_cast<const char*>(&dummy), sizeof(product));
    }
    
    --products_cnt;
    return true;
}