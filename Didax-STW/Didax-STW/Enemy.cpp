#include "Enemy.h"

Enemy::Enemy(const nlohmann::json& enemyData, const std::string& nam):m_data{enemyData}, m_name{nam}
{
	m_disabling = m_data["disabling"];
	m_standardMinus = m_data["minus"];
	m_deviation = m_data["deviation"];
}

void Enemy::play(std::vector<std::string>& board, const StatusValues& status) const
{
	if (m_data.contains("swap"))
		swap(board, status);
	if (m_data.contains("addAction") && m_data.contains("enemyAction"))
		addAction(board, status);
	if (m_data.contains("reverse"))
		reverse(board, status);
}

bool Enemy::disablingSpecial() const
{
	return m_disabling;
}

StatusValues Enemy::getMinus(const StatusValues& status) const
{
	auto base = m_standardMinus - m_deviation / 2;
	int first = (rand() % 100) * m_deviation.first/100;
	int second = (rand() % 100) * m_deviation.second/100;
	int third = (rand() % 100) * m_deviation.third/100;
	return base + StatusValues{first, second, third};
}

void Enemy::swap(std::vector<std::string>& board, const StatusValues& status) const
{
	if (rand() % 100 >= m_data["swap"])
		return;

	int x = 0, y = 0;
	do {
		x = rand() % board.size();
		y = rand() % board.size();
	} while (x == y);
	std::swap(board[x], board[y]);
}

void Enemy::addAction(std::vector<std::string>& board, const StatusValues& status) const
{
	if (rand() % 100 >= m_data["addAction"])
		return;

	int p = rand() % board.size();
	board[p] = m_data["enemyAction"];
}

void Enemy::reverse(std::vector<std::string>& board, const StatusValues& status) const
{
	if (rand() % 100 >= m_data["reverse"])
		return;
	std::reverse(board.begin(), board.end());
}
