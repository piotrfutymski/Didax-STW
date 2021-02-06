#pragma once
#include "Action.h"
class Hero
{
public:

	int getPB()const;
	bool minusPB(int v);

	std::vector<Action*>& getActions();

private:

	int m_PB{ 20 };
	std::vector<Action*> m_actions;

};

