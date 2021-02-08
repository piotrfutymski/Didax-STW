#pragma once
#include <string>
#include "Action.h"

class Enemy
{
public:

	Enemy(const nlohmann::json& enemyData, const std::string& nam);

	void play(std::vector<std::string>& board, const StatusValues & status)const; 

	bool disablingSpecial()const;

	StatusValues getMinus(const StatusValues& status)const;

private:

	nlohmann::json m_data;
	std::string m_name;

	bool m_disabling{ false };
	StatusValues m_standardMinus;
	StatusValues m_deviation;

	void swap(std::vector<std::string>& board, const StatusValues& status)const;
	void addAction(std::vector<std::string>& board, const StatusValues& status)const;
	void reverse(std::vector<std::string>& board, const StatusValues& status)const;

};

