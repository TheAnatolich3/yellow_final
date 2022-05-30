#include "node.h"

bool EmptyNode::Evaluate(const Date&, const std::string&) const
{
	return true;
}

EventComparisonNode::EventComparisonNode(Comparison comp, const std::string& ev)
	: _comp(comp), _event(ev){}

DateComparisonNode::DateComparisonNode(Comparison comp, const Date& date)
	: _comp(comp), _date(date){}

bool DateComparisonNode::Evaluate(const Date& dt, const std::string&) const
{
	switch (_comp)
	{
	case Comparison::Less:
		return dt < _date;
	case Comparison::LessOrEqual:
		return dt <= _date;
	case Comparison::Greater:
		return _date < dt;
	case Comparison::GreaterOrEqual:
		return _date <= dt;
	case Comparison::Equal:
		return _date == dt;
	case Comparison::NotEqual:
		return !(_date == dt);
	default:
		throw std::logic_error("Unknown operator");
	}
}

bool EventComparisonNode::Evaluate(const Date&, const std::string& ev) const
{
	switch (_comp)
	{
	case Comparison::Less:
		return ev < _event;
	case Comparison::LessOrEqual:
		return ev <= _event;
	case Comparison::Greater:
		return ev > _event;
	case Comparison::GreaterOrEqual:
		return ev >= _event;
	case Comparison::Equal:
		return ev == _event;
	case Comparison::NotEqual:
		return ev != _event;
	default:
		throw std::logic_error("Unknown operator");
	}
}

LogicalOperationNode::LogicalOperationNode(LogicalOperation lo, std::shared_ptr<Node> left, std::shared_ptr<Node> right)
	: _op(lo), _left(left), _right(right){}

bool LogicalOperationNode::Evaluate(const Date& dt, const std::string& ev) const
{
	if (_op == LogicalOperation::And)
	{
		return _left->Evaluate(dt, ev) && _right->Evaluate(dt, ev);
	}
	else if (_op == LogicalOperation::Or)
	{
		return _left->Evaluate(dt, ev) || _right->Evaluate(dt, ev);
	}
	return false;
}