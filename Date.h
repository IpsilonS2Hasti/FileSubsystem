#pragma once
#include <ctime>
#include <iostream>

class Date {
public:
    uint8_t day, month, year, hour, min, sec;
    Date();
    friend std::ostream& operator<<(std::ostream& os, const Date& date);
};