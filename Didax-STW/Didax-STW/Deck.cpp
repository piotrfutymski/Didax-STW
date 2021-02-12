#include "Deck.h"

Deck::Deck()
{
}

Deck::Deck(Game* g, const std::vector<std::string>& initDeck, Activity::ActivityType t)
{
	m_game = g;
	m_deck = initDeck;
	m_type = t;
}

const std::vector<std::string>& Deck::getDeck() const
{
	return m_deck;
}

Activity::ActivityType Deck::getType() const
{
	return m_type;
}
