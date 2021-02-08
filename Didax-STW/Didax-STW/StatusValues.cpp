#include "StatusValues.h"

StatusValues StatusValues::operator+(const StatusValues& rhs) const
{
	StatusValues res;
	res.first = first + rhs.first;
	res.second = second + rhs.second;
	res.third = third + rhs.third;
	return res;
}

StatusValues StatusValues::operator-(const StatusValues& rhs) const
{
	StatusValues res;
	res.first = first - rhs.first;
	res.second = second - rhs.second;
	res.third = third - rhs.third;
	return res;
}
