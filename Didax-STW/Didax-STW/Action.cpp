#include "Action.h"

Action::Action(const nlohmann::json& actionData, const std::wstring& nam):m_name(nam)
{
	loadFromJson(actionData);
}

int Action::getPBcost() const
{
	return m_PBcost;
}

std::wstring Action::getName() const
{
	return m_name;
}

std::wstring Action::getDescription() const
{
	return m_description;
}

std::wstring Action::getActivity() const
{
	return m_activity;
}

std::wstring Action::getSubType() const
{
	return m_subtype;
}

Action::Rarity Action::getRarity() const
{
	return m_rarity;
}

Action::StatusValues Action::getBasicValues() const
{
	return m_basic;
}

Action::StatusValues Action::getConditionalValues() const
{
	return m_conditional;
}

Action::StatusValues Action::statusBaseUpgrade(const std::vector<Action*>& board, int pos) const
{
	if (m_conditionalUpgrade == nullptr)
		return m_basic;
	return m_basic + m_conditionalUpgrade(board, pos);
}

Action::StatusValues Action::statusBonusUpgrade(const std::vector<Action*>& board, const StatusValues& actual, const StatusValues& gained, int pos) const
{
	if (m_bonusUbgrade == nullptr)
		return{ 0,0,0 };
	return m_bonusUbgrade(board, actual, gained, pos);
}

bool Action::equalSubType(const Action& rhs)
{
	if (m_subtype == rhs.m_subtype)
		return true;
	return false;
}

bool Action::condtionNextTo(const std::vector<Action*>& board, int pos, const std::string& ype)
{
	std::wstring stype = { ype.begin(), ype.end() };
	if (pos == 0)
	{
		if (board[1]->getSubType() == stype)
			return true;
		return false;
	}
	if (pos == board.size()-1)
	{
		if (board[board.size() - 2]->getSubType() == stype)
			return true;
		return false;
	}
	if (board[pos + 1]->getSubType() == stype || board[pos - 1]->getSubType() == stype)
		return true;
	return false;
}

bool Action::conditionCount(const std::vector<Action*>& board, int count, const std::string& ype)
{
	std::wstring stype = { ype.begin(), ype.end() };
	int t = 0;
	for (auto& x : board)
	{
		if (x->getSubType() == stype)
			t++;
	}
	if (t >= count)
		return true;
	return false;
}

bool Action::conditionCount(const std::vector<Action*>& board, const nlohmann::json& count)
{
	for (size_t i = 0; i < count.size(); i+=2)
	{
		if (!conditionCount(board, count[i+1], count[i]))
			return false;
	}
	return true;
}

Action::StatusValues Action::bonusOff0(const StatusValues& gained, int valueMin, int value)
{
	if (gained.first >= valueMin)
		return { 0, value, value };
	return { 0,0,0 };
}


Action::StatusValues Action::bonusPos0(const StatusValues& actual, int value)
{
	if (actual.first < actual.second && actual.first < actual.third)
		return { value, 0 ,0 };
	if(actual.second < actual.third && actual.second < actual.first)
		return { 0, value ,0 };
	if (actual.second > actual.third && actual.third < actual.first)
		return { 0, 0 ,value };
	if (actual.first == actual.second)
	{
		if(rand()%2)
			return { value, 0 ,0 };
		else
			return { 0,value, 0 };
	}
	if (actual.first == actual.third)
	{
		if (rand() % 2)
			return { value, 0 ,0 };
		else
			return { 0, 0, value };
	}
	else
	{
		if (rand() % 2)
			return { 0, value ,0 };
		else
			return { 0, 0, value };
	}
}

Action::StatusValues Action::bonusDeff0( const StatusValues& actual, int percent)
{
	if (actual.second > 100)
	{
		int w = ((actual.second - 100) * percent) / 100;
		return { w, 0, w };
	}
	return{ 0,0,0 };
		
}

void Action::loadFromJson(const nlohmann::json& actionData)
{
	if (!actionData.contains("activity") || !actionData.contains("subtype") || !actionData.contains("basic"))
	{
		Didax::Logger::log("Unable to create action with name " + std::string{ m_name.begin(), m_name.end() }, Didax::Logger::Level::Warn);
		return;
	}
	m_activity =  jsonToWstring(actionData["activity"]);
	m_subtype = jsonToWstring(actionData["subtype"]);
	m_basic = statusFromJsonTab(actionData["basic"]);
	if (actionData.contains("description"))
		m_description = jsonToWstring(actionData["description"]);
	if (actionData.contains("rarity"))
		setRarity(actionData["rarity"]);
	if (actionData.contains("conditional"))
		m_conditional = statusFromJsonTab(actionData["conditional"]);
	if (actionData.contains("onCond"))
		addConditionalUpgrades(actionData["onCond"]);
	if (actionData.contains("onBonus"))
		addBonusUpgrades(actionData["onBonus"]);
}

void Action::setRarity(const std::string& rar)
{
	if (rar == "normal")
		m_rarity = Rarity::Normal;
	else if (rar == "silver")
		m_rarity = Rarity::Silver;
	else if (rar == "gold")
		m_rarity = Rarity::Gold;
}

std::wstring Action::jsonToWstring(const nlohmann::json& str)
{
	std::string r = str;
	return std::wstring(r.begin(), r.end());
}

Action::StatusValues Action::statusFromJsonTab(const nlohmann::json& tab)
{
	return StatusValues{tab[0],tab[1],tab[2]};
}

void Action::addConditionalUpgrades(const nlohmann::json& onCond)
{
	m_conditionalUpgrade = [&onCond](const std::vector<Action*>& board, int pos) {
		Action::StatusValues res{ 0, 0 ,0 };
		for (auto& bonus : onCond)
		{
			bool addBonusFlag = true;
			if (bonus["conditions"].contains("count"))
				addBonusFlag = addBonusFlag && Action::conditionCount(board, (const nlohmann::json &)(bonus["conditions"]["count"]));
			if (bonus["conditions"].contains("nextTo"))
				addBonusFlag = addBonusFlag && Action::condtionNextTo(board, pos, bonus["conditions"]["nextTo"]);
			if(bonus["conditions"].contains("position"))
				addBonusFlag = addBonusFlag && (pos == bonus["conditions"]["position"] - 1);
			if (!addBonusFlag)
				continue;

			if (bonus["result"].contains("add"))
				res = res + Action::statusFromJsonTab(bonus["result"]["add"]);
			if(bonus["result"].contains("addConditional") && bonus["result"]["addConditional"])
				res = res + board[pos]->getConditionalValues();				
		}
		return res;
	};
}

void Action::addBonusUpgrades(const nlohmann::json& onBonus)
{
	m_bonusUbgrade = [&onBonus](const std::vector<Action*>& boatd, const StatusValues& actual, const StatusValues& gained, int pos) {
		Action::StatusValues res{ 0, 0 ,0 };
		if (onBonus[0] == "offBonus0")
			return Action::bonusOff0(gained, onBonus[1], onBonus[2]);
		if (onBonus[0] == "deffBonus0")
			return Action::bonusDeff0(actual, onBonus[1]);
		if (onBonus[0] == "posBonus0")
			return Action::bonusPos0(actual, onBonus[1]);
		return res;
	};
}
