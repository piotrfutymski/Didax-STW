#include "Enemy.h"

std::wstring Enemy::getName() const
{
	return m_name;
}

Action::StatusValues Enemy::getStatusValuesDown() const
{
	return m_min + Action::StatusValues{(rand() % 100)* m_range.first / 100, (rand() % 100)* m_range.second / 100, (rand() % 100)* m_range.third / 100};
}
