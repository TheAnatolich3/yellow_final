#pragma once
#include <string>
#include <memory>
#include "date.h"

class Date;

enum class Comparison
{
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual
};

enum class LogicalOperation
{
	Or,
	And
};

class Node
{
public:
	virtual bool Evaluate(const Date&, const std::string&) const = 0;
};


class EmptyNode : public Node
{
public:
	bool Evaluate(const Date&, const std::string&) const override;
};

class DateComparisonNode : public Node
{
public:
	DateComparisonNode(Comparison, const Date&);
	bool Evaluate(const Date&, const std::string&) const override;
private:
	Comparison _comp;
	Date _date;
};

class EventComparisonNode : public Node
{
public:
	EventComparisonNode(Comparison, const std::string&);
	bool Evaluate(const Date&, const std::string&) const override;
private:
	Comparison _comp;
	std::string _event;
};

class LogicalOperationNode : public Node
{
public:
	LogicalOperationNode(LogicalOperation, std::shared_ptr<Node>, std::shared_ptr<Node>);
	bool Evaluate(const Date&, const std::string&) const override;
private:
	LogicalOperation _op;
	std::shared_ptr<Node> _left, _right;
};