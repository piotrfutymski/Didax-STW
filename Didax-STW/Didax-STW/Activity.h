#pragma once
#include "Action.h"
#include "Hero.h"
#include "Enemy.h"


class Activity
{
public:
	Activity(Hero* hero, Enemy * enemy);

	const std::vector<Action*>& getOnHandActions()const;

	const std::vector<Action*>& getOnBoardActions()const;

	Action::StatusValues getStatus()const;

	Action::StatusValues getHeroAddedStatus()const;

	Action::StatusValues geEnemyRemovedStatus()const;

	void startTurn();

	void setOnBoard(int handPos, int boardPos);

	void removeFromBoard(int handPos, int boardPos);

	void acceptBoard();

	Action::StatusValues playAction(int pos);

	Action::StatusValues playBonus(int pos);

	void playEnemy();


private:
	bool m_chosingActions{ true };
	Hero* m_hero;
	Enemy* m_enemy;
	std::vector<Action*> m_onHandActions;

	std::vector<Action*> m_onBoardActions;

	Action::StatusValues m_status{ 50,50,50 };
	Action::StatusValues m_heroAdded;
	Action::StatusValues m_enemyRemoved;

};

