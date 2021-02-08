#include "StatusValues.h"

StatusValues::StatusValues(const nlohmann::json& stat)
{
	first = stat[0];
	second = stat[1];
	third = stat[2];
}

StatusValues::StatusValues()
{
	StatusValues(0, 0, 0);
}

StatusValues::StatusValues(int a, int b, int c)
{
	first = a;
	second = b;
	third = c;
}

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

StatusValues StatusValues::operator/(int rhs) const
{
	StatusValues res;
	res.first = first / rhs;
	res.second = second / rhs;
	res.third = third / rhs;
	return res;
}

StatusValues StatusValues::operator*(int rhs) const
{
	StatusValues res;
	res.first = first * rhs;
	res.second = second * rhs;
	res.third = third * rhs;
	return res;
}

int StatusValues::getValue(int num) const
{
	if (num == 0)
		return first;
	if (num == 1)
		return second;
	if (num == 2)
		return third;
	return -1;
}

void StatusValues::setValue(int num, int v)
{
	if (num == 0)
		first = v;
	if (num == 1)
		second = v;
	if (num == 2)
		third = v;
}
