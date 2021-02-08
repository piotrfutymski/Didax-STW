#pragma once
#include <string>
#include <vector>
#include <functional>

#include "Didax-Engine/Engine.h"
#include "StatusValues.h"

class Action
{

public:
	enum class Rarity{
		Normal, Silver, Gold
	};

	Action(const nlohmann::json & actionData, const std::string& nam);

	StatusValues getUpgrade(const std::vector<std::string>& board, int pos);

	StatusValues getBonus(const std::vector<std::string>& board, int pos, const StatusValues& actual, const StatusValues& gained);

	int getBonusChanges(const std::vector<std::string>& board, int pos, const StatusValues& actual, const StatusValues& gained);


	int getPBcost()const;

	std::wstring getName()const;

	std::wstring getDescription()const;

	std::wstring getActivity()const;

	std::wstring getSubType()const;

	Rarity getRarity()const;

	StatusValues getBasicValues()const;

	StatusValues getConditionalValues()const;

	StatusValues statusBaseUpgrade(const std::vector<Action*>& board, int pos)const;

	StatusValues statusBonusUpgrade(const std::vector<Action*>& board, const StatusValues& actual, const StatusValues& gained, int pos) const;

	bool equalSubType(const Action& rhs);

	static bool condtionNextTo(const std::vector<Action*>& board, int pos, const std::string& stype);
	static bool conditionCount(const std::vector<Action*>& board, int count, const std::string& stype);
	static bool conditionCount(const std::vector<Action*>& board, const nlohmann::json& count);
	static StatusValues bonusOff0(const StatusValues& gained, int valueMin, int value);
	static StatusValues bonusPos0(const StatusValues& gained, int value);
	static StatusValues bonusDeff0(const StatusValues& actual, int percent);
	static StatusValues statusFromJsonTab(const nlohmann::json& tab);

private:

	std::wstring m_name;
	std::wstring m_description{};
	std::wstring m_activity{};
	std::wstring m_subtype{};

	Rarity m_rarity{Rarity::Normal};

	StatusValues m_basic{0,0,0};
	StatusValues m_conditional{0,0,0};

	int m_PBcost{0};

private:

	std::function< StatusValues(const std::vector<Action*>& board, int pos) > m_conditionalUpgrade;
	std::function< StatusValues(const std::vector<Action*>& boatd, const StatusValues& actual, const StatusValues& gained, int pos)> m_bonusUbgrade;

	void loadFromJson(const nlohmann::json& actionData);
	void setRarity(const std::string& rar);
	
	std::wstring jsonToWstring(const nlohmann::json& str);

	void addConditionalUpgrades(const nlohmann::json& onCond);
	void addBonusUpgrades(const nlohmann::json& onBonus);



};

