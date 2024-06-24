#include "Date.h"

Date::Date() {
    std::time_t t = std::time(nullptr);
    std::tm* now = std::localtime(&t);

    year = now->tm_year % 100;
    month = now->tm_mon + 1;
    day = now->tm_mday;
    hour = now->tm_hour;
    min = now->tm_min;
    sec = now->tm_sec;
}

std::ostream& operator<<(std::ostream& os, const Date& date){
    os << (date.year < 10 ? "0" : "") << static_cast<int>(date.day) << "/"
       << (date.month < 10 ? "0" : "") << static_cast<int>(date.month) << "/"
       << (date.day < 10 ? "0" : "") << static_cast<int>(date.year) << " "
       << (date.hour < 10 ? "0" : "") << static_cast<int>(date.hour) << ":"
       << (date.min < 10 ? "0" : "") << static_cast<int>(date.min) << ":"
       << (date.sec < 10 ? "0" : "") << static_cast<int>(date.sec);
    return os;
}