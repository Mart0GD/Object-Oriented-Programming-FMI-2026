#include <iostream>
#include <iomanip>

// Structure definition
struct Date {
	unsigned short day;     // Uninitialized member - the value is undefined
	unsigned short month;   // Uninitialized member - the value is undefined
	unsigned short year;    // Uninitialized member - the value is undefined
};

struct Time {
	unsigned short hour = 0;        // Initialized member - the value is 0
	unsigned short minute{};        // Initialized member - the value is 0
	unsigned short second{15};      // Initialized member - the value is 15
};

const int kMaxNameSize = 50;

struct Employee {
	int id{ 0 };
	char name[kMaxNameSize]{};
	double salary{ 10000.0 };

	Date hireDate{}; // A struct, can have another struct as a member
};

struct Point {
	int x;
	int y;
};

void printDate(const Date& date);
void printTime(const Time& time);

int main() {
	// Defining a struct object
	Date birthday; 
	Time randomTime; 
    
    // Member access
	birthday.day = 17;
	birthday.month = 7;
	birthday.year = 2002;

	std::cout << "I was born on ";
	printDate(birthday);

	std::cout << "Random time: ";
	printTime(randomTime);

	// Struct initialization
	Date today = { 24, 2, 2026 };

	std::cout << "Today is ";
	printDate(today);

	// Another way to initialize a struct
	Time randomTime2{ 12, 30, 45 };

	std::cout << "Random time 2: ";
	printTime(randomTime2);

	// If the struct has members that have a default value, we can omit them
	// But we should not mix the order of the members
	Time randomTime3{ 12, 30 };

	std::cout << "Random time 3: ";
	printTime(randomTime3);

	// Const structs
	// The members of a const (or constexpr) struct cannot be modified
	const Date newYear{ 1, 1, 2025 };
	// newYear.day = 2; // Error: newYear is const

	// Employee struct
	Employee employee{ 1, "John Doe", 2000.0, { 1, 1, 2020 } };

	// Passing temporary structs
	printDate(Date { 23, 3, 2025 });
	// printDate({ 23, 3, 2025 }); - Struct type can be omitted

	// Returning a struct from a function
	Point zeroPoint1 = {0,0};
	Point zeroPoint2{0,0};
	Point zeroPoint3 = Point{1,2};

	std::cout << "Zero point 1: " << zeroPoint1.x << ", " << zeroPoint1.y << std::endl;
	std::cout << "Zero point 2: " << zeroPoint2.x << ", " << zeroPoint2.y << std::endl;
	std::cout << "Zero point 3: " << zeroPoint3.x << ", " << zeroPoint3.y << std::endl;

	return 0;
}

void printDate(const Date& date) {
    std::cout << date.day << '/' << date.month << '/' << date.year << std::endl;
}

void printTime(const Time& time) {
	std::cout << time.hour << ':' << time.minute << ':' << time.second;
}
