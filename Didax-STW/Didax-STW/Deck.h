#pragma once
#include "Activity.h"

class Game;

class Deck
{
public:

	Deck(Game* g, const std::vector<std::string> & initDeck, Activity::ActivityType t);

	const std::vector<std::string>& getDeck()const;

	Activity::ActivityType getType()const;

private:

	Game* m_game;
	std::vector<std::string> m_deck;
	Activity::ActivityType m_type;

};

