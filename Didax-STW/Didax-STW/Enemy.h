#pragma once
#include <string>
#include "Action.h"

class Enemy
{
public:

	std::wstring getName()const;

	Action::StatusValues getStatusValuesDown()const;

private:

	std::wstring m_name{ L"wolf" };
	std::wstring m_activity{ L"fight" };

	Action::StatusValues m_min{15,25,15};
	Action::StatusValues m_range{10,10,10};

};

