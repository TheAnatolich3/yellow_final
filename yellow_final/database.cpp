#include <algorithm>
#include "date.h"
#include "database.h"

void Database::Add(const Date& dt, std::string ev)
{
	if (_data.count(dt) != 0 && _check_unique_events.count(dt.to_string() + ev))
	{
		return;
	}
	_data[dt].push_back(ev);
	_check_unique_events.insert(dt.to_string() + ev);
}

void Database::Print(std::ostream& out) const
{
	for (const auto& event : _data)
	{
		for (const auto& event_name : event.second)
		{
			out << event.first << ' ' << event_name << std::endl;
		}
	}
}

std::string Database::Last(Date dt) const
{
	auto it = _data.upper_bound(dt);
	if (it == _data.begin())
	{
		throw std::invalid_argument{""};
	}

	it = std::prev(it);
	return it->first.to_string() + ' ' + it->second[it->second.size() - 1];
}

int Database::RemoveIf(const std::function<bool(const Date&, const std::string&)> predicate)
{
	int counter = 0;
	for (auto& item : _data)
	{
		auto& date = item.first;
		auto& events = item.second;
		for (auto it = events.begin(); it != events.end();)
		{
			if (predicate(date, *it))
			{
				++counter;
				_check_unique_events.erase(date.to_string() + *it);
				it = events.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	for (auto it = _data.begin(); it != _data.end(); )
	{
		if (it->second.empty())
		{
			it = _data.erase(it);
		}
		else
		{
			++it;
		}
	}
	return counter;
}

std::vector<std::pair<Date, std::string>> Database::FindIf(const std::function<bool(Date, std::string)> predicate) const
{
	std::vector<std::pair<Date, std::string>> res;
	for (auto& item : _data)
	{
		for (auto& event : item.second)
		{
			if (predicate(item.first, event))
			{
				res.push_back({item.first, event});
			}
		}
	}
	return res;
}