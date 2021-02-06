#include "Activity.h"

Activity::Activity(Hero* hero, Enemy* enemy):m_hero{hero}, m_enemy{enemy}
{
	m_onBoardActions.resize(4);
	m_onHandActions.resize(6);
}

const std::vector<Action*>& Activity::getOnHandActions() const
{
	return m_onHandActions;
}

const std::vector<Action*>& Activity::getOnBoardActions() const
{
	return m_onBoardActions;
}

Action::StatusValues Activity::getStatus() const
{
	return m_status;
}

Action::StatusValues Activity::getHeroAddedStatus() const
{
	return m_heroAdded;
}

Action::StatusValues Activity::geEnemyRemovedStatus() const
{
	return m_enemyRemoved;
}

void Activity::startTurn()
{
	m_heroAdded = { 0,0,0 };
	m_enemyRemoved = { 0,0,0 };
	for (auto& x : m_onBoardActions)
		x = nullptr;
	for (auto& x : m_onHandActions)
	{
		Action* v = nullptr;
		if (x != nullptr)
			continue;
		while (std::find(m_onHandActions.begin(), m_onHandActions.end(), v) != m_onHandActions.end())
		{		
			v = m_hero->getActions()[std::rand() % m_hero->getActions().size()];
		}
		x = v;
	}
}

void Activity::setOnBoard(int handPos, int boardPos)
{
	if (m_onHandActions[handPos] != nullptr && m_onBoardActions[boardPos] == nullptr)
	{
		m_onBoardActions[boardPos] = m_onHandActions[handPos];
		m_onHandActions[handPos] = nullptr;
	}
}

void Activity::removeFromBoard(int handPos, int boardPos)
{
	if (m_onHandActions[handPos] == nullptr && m_onBoardActions[boardPos] != nullptr)
	{
		m_onHandActions[handPos] = m_onBoardActions[boardPos];
		m_onHandActions[boardPos] = nullptr;
	}
}

void Activity::acceptBoard()
{
}

Action::StatusValues Activity::playAction(int pos)
{
	auto res = m_onBoardActions[pos]->statusBaseUpgrade(m_onBoardActions, pos);
	m_heroAdded = m_heroAdded + res;
	m_status = m_status + res;
	return res;
}

Action::StatusValues Activity::playBonus(int pos)
{
	auto res = m_onBoardActions[pos]->statusBonusUpgrade(m_onBoardActions, m_status, m_heroAdded, pos);
	m_heroAdded = m_heroAdded + res;
	m_status = m_status + res;
	return res;
}

void Activity::playEnemy()
{
	m_enemyRemoved = m_enemy->getStatusValuesDown();
	m_status = m_status - m_enemyRemoved;
}
