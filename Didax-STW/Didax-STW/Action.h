#pragma once
#include <string>
#include <vector>
#include <functional>

#include "Didax-Engine/Engine.h"
#include "StatusValues.h"

class Game;

class Action
{

public:
	enum class Rarity{
		Normal, Silver, Gold
	};

	Action(const nlohmann::json & actionData, const std::string& nam, Game * g);

	StatusValues getUpgrade(const std::vector<std::string>& board, int pos);

	StatusValues getBonus(const std::vector<std::string>& board, int pos, const StatusValues& actual, const StatusValues& gained);

	int getBonusChanges(const std::vector<std::string>& board, int pos, const StatusValues& actual, const StatusValues& gained);
	
	//getters

	int getPBcost()const;

	std::string getName()const;

	Rarity getRarity()const;

	std::string getType()const;

private:

	Game* m_game;

	nlohmann::json m_data;
	std::string m_name;
	std::string m_activity;
	std::string m_subtype;

	Rarity m_rarity{Rarity::Normal};
	int m_PBcost{ 0 };

	StatusValues m_basicValues{0,0,0};
	std::vector<StatusValues> m_conditional;

private:

	void loadFromJson(const nlohmann::json& actionData);
	void setRarity(const std::string& rar);
	void loadConditional(const nlohmann::json& conditional);
	StatusValues randValue(const StatusValues& mini, const StatusValues& maxi);

	//upgrades
	
	StatusValues upgradeValue(const std::vector<std::string>& board, int pos);
	StatusValues nextToUpgrade(const nlohmann::json& info, const std::vector<std::string>& board, int pos);
	StatusValues onPositionUpgrade(const nlohmann::json& info, const std::vector<std::string>& board, int pos);
	StatusValues countUpgrade(const nlohmann::json& info, const std::vector<std::string>& board, int pos);

	bool conditionNextToType(const std::string& type, int n, const std::vector<std::string>& board, int pos);
	bool conditionNextToName(const std::string& name, const std::vector<std::string>& board, int pos);
	bool conditionCount(const std::string& type, int n, const std::vector<std::string>& board, int pos);

	//bonuses
	
	StatusValues bonusDef0(const nlohmann::json& info, const StatusValues& actual);
	StatusValues bonusOff0(const nlohmann::json& info, const StatusValues& gained);


};

