#pragma once
#include <nlohmann/json.hpp>

class StatusValues
{
public:
	int first;
	int second;
	int third;

	StatusValues(const nlohmann::json& stat);
	StatusValues();
	StatusValues(int, int, int);

	StatusValues operator+(const StatusValues& rhs)const;
	StatusValues operator-(const StatusValues& rhs)const;
	StatusValues operator/(int rhs)const;
	StatusValues operator*(int rhs)const;

	int getValue(int num)const;

	void setValue(int num, int v);

};

