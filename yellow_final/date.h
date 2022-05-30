#pragma once
#include <sstream>

class Date
{
public:
    Date() = default;

    Date(int year, int month, int day)
        : _year(year), _month(month), _day(day) {}

    Date(const Date& dt)
        : _year(dt._year), _month(dt._month), _day(dt._day) {}

    bool operator<(const Date& dt) const;
    bool operator<=(const Date& dt) const;
    bool operator==(const Date& dt) const;
    
    std::string to_string() const;

    friend std::istream& operator>>(std::istream& in, Date& dt);
    friend std::ostream& operator<<(std::ostream& out, const Date& dt);
private:
    int _year;
    int _month;
    int _day;
};


Date ParseDate(std::istream& is);