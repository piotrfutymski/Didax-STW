#include "Activity.h"
#include "Game.h"

Activity::Activity(const nlohmann::json& data, Hero* hero, Game* game)
{
	m_hero = hero;
	m_game = game;
	initTypeFromString(data["activityType"]);
	m_enemy = data["enemy"];
	m_descriptionWidg = data["descWidg"];
	m_actualStatus = hero->getInitialStatus(m_type);
	m_beginTurnStatus = m_actualStatus;
	m_disablingEnemy = m_game->getEnemy(m_enemy)->disablingSpecial();
	randBoard();
}

bool Activity::finished() const
{
	return m_finished;
}

bool Activity::won() const
{
	return m_won;
}

bool Activity::canChangeAction() const
{
	if (m_changeStacks > 0 && m_state == State::PlayerChoosing)
		return true;
	return false;
}

void Activity::changeAction(int num)
{
	if (!canChangeAction())
		return;
	if (m_onHandActions[num] == "")
		return;
	m_onHandActions[num] = randAction();
	m_changeStacks--;
}

void Activity::setOnBoard(int handPos, int boardPos)
{
	if (m_onHandActions[handPos] == "" || m_onBoardActions[boardPos] != "" || m_state != State::PlayerChoosing)
		return;
	m_onHandActions[handPos] = "";
	m_onBoardActions[boardPos] = m_onHandActions[handPos];
}

void Activity::removeFromBoard(int handPos, int boardPos)
{
	if (m_onHandActions[handPos] != "" || m_onBoardActions[boardPos] == "" || m_state != State::PlayerChoosing)
		return;
	m_onBoardActions[boardPos] = "";
	m_onHandActions[handPos] = m_onBoardActions[boardPos];
}

bool Activity::canMakeFightSpecial(int num) const
{
	if (m_type != ActivityType::Fight || m_state != State::PlayerChoosing || m_disablingEnemy)
		return false;
	if(m_actualStatus.getValue(num) > 100)
		return true;
	return false;
}

bool Activity::fightSpecial(int num)
{
	if(!canMakeFightSpecial(num))
		return false;
	int v = 50;
	if (m_actualStatus.getValue(num) < 150)
	{
		v = m_actualStatus.getValue(num) - 100;
		m_actualStatus.setValue(num, 100);
	}
	else
		m_actualStatus.setValue(num, m_actualStatus.getValue(num) - 50);
	m_beginTurnStatus = m_actualStatus;
	
	int s = rand() % 100;
	if (s < v)
	{
		m_finished = true;
		m_won = true;
		return true;
	}
	else
		return false;
}

bool Activity::canMakeTalkSpecial() const
{
	if (statusesbiggerEqual100() > talkToStay.size() && m_state == State::PlayerChoosing && !m_disablingEnemy)
		return true;
	return false;
}

void Activity::talkSpecial(int num)
{
	if (canMakeTalkSpecial() && num >= 0 && num < m_onBoardActions.size())
		talkToStay.push_back(num);
}

void Activity::backTalkSpecial(int num)
{
	talkToStay.erase(std::remove(talkToStay.begin(), talkToStay.end(), num), talkToStay.end());
}

bool Activity::canEndTurn() const
{
	for (auto& x : m_onBoardActions)
	{
		if (x == "")
			return false;
	}
	if (m_hero->getPB() < getPBCostOfBoard())
		return false;
	return true;
}

void Activity::acceptBoard()
{
	if (!canEndTurn())
		return;

	m_state = State::EnemyChoosing;
	m_hero->minusPB(getPBCostOfBoard());
}

void Activity::playEnemy()
{
	if (m_state != State::EnemyChoosing)
		return;
	m_game->getEnemy(m_enemy)->play(m_onBoardActions, m_actualStatus);
	m_state = State::Upgrading;
}

bool Activity::isNextUpgrade() const
{
	return m_state == State::Upgrading;
}

StatusValues Activity::nextUpgrade()
{
	StatusValues res{};
	if (m_state != State::Upgrading)
		return res;

	res = m_game->getAction(m_onBoardActions[m_numOfNextAction])->getUpgrade(m_onBoardActions, m_numOfNextAction);
	m_actualStatus = m_actualStatus + res;
	m_upgradeGained = m_upgradeGained + res;
	m_numOfNextAction++;
	if (m_numOfNextAction == m_onBoardActions.size())
	{
		m_state = State::Bonuses;
		m_numOfNextAction = 0;
	}
	return res;
}

bool Activity::isNextBonus() const
{
	return m_state == State::Bonuses;
}

StatusValues Activity::nextBonus()
{
	StatusValues res{};
	if (m_state != State::Bonuses)
		return res;
	auto a = m_game->getAction(m_onBoardActions[m_numOfNextAction]);
	res = a->getBonus(m_onBoardActions, m_numOfNextAction, m_actualStatus, m_upgradeGained);
	m_changeStacks += a->getBonusChanges(m_onBoardActions, m_numOfNextAction, m_actualStatus, m_upgradeGained);

	m_actualStatus = m_actualStatus + res;
	m_numOfNextAction++;
	if (m_numOfNextAction == m_onBoardActions.size())
	{
		m_state = State::EnemyMinus;
		m_numOfNextAction = 0;
	}
	return res;
}

bool Activity::isEnemy() const
{
	return m_state == State::EnemyMinus;
}

StatusValues Activity::enemyMinus()
{
	StatusValues res{};
	if (m_state != State::EnemyMinus)
		return res;

	res = m_game->getEnemy(m_enemy)->getMinus(m_actualStatus);
	m_actualStatus = m_actualStatus - res;
	m_state = State::Ending;
	return res;
}

void Activity::nextTurn()
{
	if (m_state != State::Ending)
		return;
	m_beginTurnStatus = m_actualStatus;
	m_upgradeGained = {};
	for (int i = 0; i < m_onBoardActions.size(); i++)
	{
		if (std::find(talkToStay.begin(), talkToStay.end(), i) == talkToStay.end())		// if not found
			m_onBoardActions[i] = "";
	}
	randBoard();
	m_state = State::PlayerChoosing;
	m_numOfNextAction = 0;
	talkToStay.clear();
	if (statusesbiggerEqual100() == 3)		// check if won
	{
		m_finished = true;
		m_won = true;
	}
	else if (m_actualStatus.first <= 0 || m_actualStatus.second <= 0 || m_actualStatus.third <= 0)	// check if loose
	{
		m_finished = true;
		m_won = false;
	}
}

const std::vector<std::string>& Activity::getOnHandActions() const
{
	return m_onHandActions;
}

const std::vector<std::string>& Activity::getOnBoardActions() const
{
	return m_onBoardActions;
}

StatusValues Activity::getBeginTurnStatus() const
{
	return m_beginTurnStatus;
}

StatusValues Activity::getActualStatus() const
{
	return m_actualStatus;
}

int Activity::getChangeStacks() const
{
	return m_changeStacks;
}

std::string Activity::getEnemy() const
{
	return m_enemy;
}

std::string Activity::getDescription() const
{
	return m_descriptionWidg;
}

Activity::ActivityType Activity::getType() const
{
	return m_type;
}

void Activity::initTypeFromString(const std::string& t)
{
	if (t == "Fight")
		m_type = ActivityType::Fight;
	else if (t == "Exploration")
		m_type = ActivityType::Exploration;
	else if (t == "Talk")
		m_type = ActivityType::Talk;
}

void Activity::randBoard()
{
	for (int i = 0; i < m_onHandActions.size(); i++)
		if (m_onHandActions[i] == "")
			m_onHandActions[i] = randAction();
}

std::string Activity::randAction()
{
	std::string res;
	auto& deck = m_hero->getDeck(m_type).getDeck();
	do {
		res = deck[rand() %deck.size()];

	} while (std::find(m_onHandActions.begin(), m_onHandActions.end(), res) != m_onHandActions.end());
	return res;
}

int Activity::statusesbiggerEqual100() const
{
	int res = 0;
	for (int i = 0; i < 3; i++)
	{
		if (m_actualStatus.getValue(i) >= 100)
			res++;
	}
	return res;
}

int Activity::getPBCostOfBoard() const
{
	int res = 0;
	for (auto& x : m_onBoardActions)
	{
		int v = m_game->getAction(x)->getPBcost();
		if (m_type == ActivityType::Exploration && v > 0 && statusesbiggerEqual100() > 0 && !m_disablingEnemy)
			v--;
		res += v;
	}
	return res;
}
