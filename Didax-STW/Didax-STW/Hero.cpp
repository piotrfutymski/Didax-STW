#include "Hero.h"

int Hero::getPB() const
{
	return m_PB;
}

bool Hero::minusPB(int v)
{
	if (v > m_PB)
		return false;
	m_PB -= v;
	return true;
}

std::vector<Action*>& Hero::getActions()
{
	return m_actions;
}
