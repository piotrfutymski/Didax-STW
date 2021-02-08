#include "Hero.h"

Hero::Hero()
{
}

void Hero::init(const nlohmann::json& heroData, Game* parent)
{
	m_game = parent;
	m_maxPB = heroData["startingPB"];
	m_PB = m_maxPB;
	for (auto& x : heroData["startActions"])
		m_actions.push_back(x);

	std::vector<std::string> startingFight;
	for (auto& x : heroData["startingFightDeck"])
		startingFight.push_back(x);

	m_fightDeck = Deck(m_game, startingFight, Activity::ActivityType::Fight);

}

StatusValues Hero::getInitialStatus(Activity::ActivityType t) const
{
	return{ 50,50,50 };
}

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

const Deck& Hero::getDeck(Activity::ActivityType t) const
{
	if (t == Activity::ActivityType::Fight)
		return m_fightDeck;
}
