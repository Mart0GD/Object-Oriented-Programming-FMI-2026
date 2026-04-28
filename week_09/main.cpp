#include <iostream>
#include <fstream>
#include "Task.hpp"
#include "Schedule.hpp"

int main(void){

    Task t1("Do dishes", 320, 50);
    Task t2("Clean", 400, 90);
    Task t3("Watch TV", 1, 65);

    Task t1_cpy = t1;

    Schedule monday("Monday");

    // Добавяне на задача 
    monday.add_task(t1, 12, 30);

    // Добавяне на по-приоритетна 
    monday.add_task(t2, 11, 01);

    // Добавяне с по-нисък приоритет
    bool flag = monday.add_task(t3, 11, 20);
    if(!flag) std::cerr << "Can't watch TV before cleaning!\n";

    // Добавяне с невалидно време 
    flag = monday.add_task(Task("Play golf", 100, 10), 23, 56);
    if(!flag) std::cerr << "Invalid task time!";

    monday.add_task(t1, 8, 00);
    monday.add_task(Task ("Random", 10, 4), 8, 50);
    monday.add_task(t3, 14, 30);

    // Принтиране на всички задача в 8 часа
    monday.print_tasks_in_hour(8);
    

    Task* task_in_8_00_am = monday.get_task(8,0);
    Task* task_in_8_59_am = monday.get_task(8,59); // Няма такава
 
    std::ofstream write("File.txt");
    
    Schedule::serialize(write, monday);
    Schedule empty;

    write.flush();
    std::ifstream is("File.txt");

    Schedule::deserialize(is, empty);
    return 0;
}