#include "Action.h"
#include "Game.h"

void Action::loadFromJson(const nlohmann::json& actionData)
{
	if (!actionData.contains("activity") || !actionData.contains("subtype") || !actionData.contains("basicValues"))
	{
		Didax::Logger::log("Unable to create action with name " + std::string{ m_name.begin(), m_name.end() }, Didax::Logger::Level::Warn);
		return;
	}
	m_activity = actionData["activity"];
	m_subtype = actionData["subtype"];
	m_basicValues = actionData["basicValues"];
	
	if (actionData.contains("rarity"))
		setRarity(actionData["rarity"]);
	if (actionData.contains("conditional"))
		loadConditional(actionData["conditional"]);
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

void Action::loadConditional(const nlohmann::json& conditional)
{
	for (auto& x : conditional)
		m_conditional.push_back(StatusValues(x["values"]));
}

StatusValues Action::upgradeValue(const std::vector<std::string>& board, int pos)
{
	if (!m_data.contains("upgrades"))
		return {0,0,0};
	StatusValues res;
	for (auto& el : m_data["upgrades"].items())
	{
		if (el.value()["name"] == "nextTo")
			res = res + nextToUpgrade(el.value(), board, pos);
		else if (el.value()["name"] == "onPosition")
			res = res + onPositionUpgrade(el.value(), board, pos);
		else if (el.value()["name"] == "count")
			res = res + countUpgrade(el.value(), board, pos);
	}
	return res;
}

StatusValues Action::nextToUpgrade(const nlohmann::json& info, const std::vector<std::string>& board, int pos)
{
	bool adder = true;
	for (int i = 0; i < info["types"].size(); i+=2)
	{
		if (!conditionNextToType(info["types"][i], info["types"][i + 1L], board, pos))
		{
			adder = false;
			break;
		}	
	}
	for (int i = 0; i < info["names"].size(); i++)
	{
		if (!conditionNextToName(info["names"][i], board, pos))
		{
			adder = false;
			break;
		}
	}
	if (!adder)
		return {0,0,0};
	return m_conditional[info["reward"]];
}

StatusValues Action::onPositionUpgrade(const nlohmann::json& info, const std::vector<std::string>& board, int pos)
{
	if(!pos == info["position"])
		return { 0,0,0 };
	return m_conditional[info["reward"]];
}

StatusValues Action::countUpgrade(const nlohmann::json& info, const std::vector<std::string>& board, int pos)
{
	bool adder = true;
	for (int i = 0; i < info["types"]; i += 2)
	{
		if (!conditionCount(info["types"][i], info["types"][i+1L],board, pos))
		{
			adder = false;
			break;
		}
	}
	if (!adder)
		return { 0,0,0 };
	return m_conditional[info["reward"]];
}

bool Action::conditionNextToType(const std::string& type, int n, const std::vector<std::string>& board, int pos)
{
	std::vector<std::string> types{ board.size() };
	for (int i = 0; i < board.size(); i++)
	{
		types[i] = m_game->getAction(board[i])->getType();
	}
	if (n == 1)
	{
		return conditionNextToName(type, types, pos);
	}
	else if (n == 2)
	{
		if (pos == 0 || pos == board.size() - 1)
			return false;
		if (types[pos - 1L] == type && types[pos + 1L] == type)
			return true;
	}
	return false;
}

bool Action::conditionNextToName(const std::string& name, const std::vector<std::string>& board, int pos)
{
	if (pos == 0)
	{
		if (board[1] == name)
			return true;
	}
	else if (pos == board.size() - 1)
	{
		if (board[board.size() - 2] == name)
			return true;
	}
	else
	{
		if (board[pos + 1L] == name || board[pos - 1L] == name)
			return true;
	}
	return false;
}

bool Action::conditionCount(const std::string& type, int n, const std::vector<std::string>& board, int pos)
{
	int t = 0;
	for (auto& x : board)
	{
		if (m_game->getAction(x)->getType() == type)
			t++;
	}
	if (t >= n)
		return true;
	return false;
}

StatusValues Action::bonusDef0(const nlohmann::json& info, const StatusValues& actual)
{
	if (actual.second > 100)
	{
		int w = ((actual.second - 100) * info["percent"]) / 100;
		return { w, 0, w };
	}
	return{ 0,0,0 };
}

StatusValues Action::bonusOff0(const nlohmann::json& info, const StatusValues& gained)
{
	if (gained.first >= info["minValue"])
		return { 0, info["value"], info["value"] };
	return { 0,0,0 };
}

StatusValues Action::randValue(const StatusValues& mini, const StatusValues& maxi)
{
	auto range = maxi - mini;
	int first = (rand() % 100) * range.first / 100;
	int second = (rand() % 100) * range.second / 100;
	int third = (rand() % 100) * range.third / 100;
	return mini + StatusValues{ first, second, third }; 
}
////////////////
Action::Action(const nlohmann::json& data, const std::string& nam, Game* g) :m_data{ data }, m_name{ nam }, m_game{ g }
{
	loadFromJson(data);
}

StatusValues Action::getUpgrade(const std::vector<std::string>& board, int pos)
{
	return m_basicValues + upgradeValue(board, pos);
}

StatusValues Action::getBonus(const std::vector<std::string>& board, int pos, const StatusValues& actual, const StatusValues& gained)
{
	if (!m_data.contains("bonus"))
		return { 0,0,0 };

	if (m_data["bonus"] = "off0")
		return bonusOff0(m_data["bonus"], gained);
	else if (m_data["bonus"] = "def0")
		return bonusDef0(m_data["bonus"], actual);

	return{ 0,0,0 };
}

int Action::getBonusChanges(const std::vector<std::string>& board, int pos, const StatusValues& actual, const StatusValues& gained)
{
	if (!m_data.contains("bonus"))
		return 0;

	if (m_data["bonus"] = "pos0")
		return 1;
	return 0;
}

int Action::getPBcost() const
{
	return m_PBcost;
}

std::string Action::getName() const
{
	return m_name;
}

Action::Rarity Action::getRarity() const
{
	return m_rarity;
}

std::string Action::getType() const
{
	return m_subtype;
}
