#include <tuple>
#include <iomanip>
#include "date.h"

Date ParseDate(std::istream& is)
{
    Date res;
    is >> res;
    return res;
}

std::istream& operator>>(std::istream& in, Date& dt)
{
    in >> dt._year;
    in.ignore(1);
    in >> dt._month;
    in.ignore(1);
    in >> dt._day;
    return in;
}


bool Date::operator<(const Date& dt) const
{
    return std::tie(_year, _month, _day) < std::tie(dt._year, dt._month, dt._day);
}

bool Date::operator<=(const Date& dt) const
{
    return std::tie(_year, _month, _day) <= std::tie(dt._year, dt._month, dt._day);
}

bool Date::operator==(const Date& dt) const
{
    return std::tie(_year, _month, _day) == std::tie(dt._year, dt._month, dt._day);
}

std::string Date::to_string() const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(4) << _year << '-' << std::setw(2) << _month << '-' << std::setw(2) << _day;
    return ss.str();
}

std::ostream& operator<<(std::ostream& out, const Date& dt)
{
    out << dt.to_string();
    return out;
}