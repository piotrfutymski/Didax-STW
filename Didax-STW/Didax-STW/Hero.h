#pragma once
#include "Deck.h"

class Game;

class Hero
{
public:

	Hero();

	void init(const nlohmann::json& heroData, Game * parent);

	StatusValues getInitialStatus(Activity::ActivityType t)const;


	int getPB()const;
	bool minusPB(int v);

	const Deck& getDeck(Activity::ActivityType t)const;

private:

	Game* m_Game;

	int m_PB{ 30 };
	std::vector<std::string> m_actions;
	Deck m_fightDeck;
	Deck m_explorationDeck;
	Deck m_TalkDeck;
};

