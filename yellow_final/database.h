#pragma once
#include <string>
#include <ostream>
#include <vector>
#include <functional>
#include <map>
#include <set>

class Date;

class Database
{
public:
	void Add(const Date& dt, std::string ev);
	void Print(std::ostream& out) const;
	int RemoveIf(const std::function<bool(const Date&, const std::string&)>);
	std::vector<std::pair<Date, std::string>> FindIf(const std::function<bool(Date, std::string)>) const;
	std::string Last(Date dt) const;
private:
	std::map<Date, std::vector<std::string>> _data;
	std::set<std::string> _check_unique_events;
};