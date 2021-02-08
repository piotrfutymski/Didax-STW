#pragma once
#include "Action.h"
#include "Enemy.h"
#include "StatusValues.h"

#include <nlohmann/json.hpp>

class Game;
class Hero;

class Activity
{
public:

	enum class ActivityType {
		Fight, Talk, Exploration
	};

	enum class State {
		PlayerChoosing, EnemyChoosing, Upgrading, Bonuses, EnemyMinus, Ending
	};


	Activity(const nlohmann::json& data, Hero* hero, Game* game);

	bool finished()const;

	bool won()const;

	//base options

	bool canChangeAction()const;

	void changeAction(int num);

	void setOnBoard(int handPos, int boardPos);

	void removeFromBoard(int handPos, int boardPos);

	//special options

	bool canMakeFightSpecial(int num)const;

	bool fightSpecial(int num);

	bool canMakeTalkSpecial()const;

	void talkSpecial(int num);

	void backTalkSpecial(int num);

	// turn end

	bool canEndTurn()const;

	void acceptBoard();

	//enemy moves

	void playEnemy();

	//calculations

	bool isNextUpgrade()const;

	StatusValues nextUpgrade();

	bool isNextBonus()const;

	StatusValues nextBonus();

	bool isEnemy()const;

	StatusValues enemyMinus();
	
	// next Turn

	void nextTurn();

	//geters

	const std::vector<std::string>& getOnHandActions()const;

	const std::vector<std::string>& getOnBoardActions()const;

	StatusValues getBeginTurnStatus()const;

	StatusValues getActualStatus()const;
	
	int getChangeStacks()const;

	std::string getEnemy()const;

	std::string getDescription()const;

	ActivityType getType()const;

	int getPBCostOfBoard()const;

private:

	ActivityType m_type;

	// table objects

	std::string m_enemy;
	std::string m_descriptionWidg;
	
	StatusValues m_actualStatus;
	StatusValues m_beginTurnStatus;
	StatusValues m_upgradeGained;

	int m_changeStacks{ 0 };

	std::vector<std::string> m_onHandActions{ 6 };
	std::vector<std::string> m_onBoardActions{ 4 };

	// game

	Hero* m_hero;
	Game* m_game;

	//state

	State m_state{ State::PlayerChoosing };
	int m_numOfNextAction{ 0 };
	bool m_finished{ false };
	bool m_won{ false };
	std::vector<int> talkToStay;

	bool m_disablingEnemy{ false };

private:

	void initTypeFromString(const std::string& t);
	void randBoard();
	std::string randAction();
	int statusesbiggerEqual100()const;

};

