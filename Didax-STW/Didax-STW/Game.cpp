#include "Game.h"

void Game::init(Didax::AssetManager* a)
{
	m_assets = a;
	auto& gameData = m_assets->getAsset<Didax::DataAsset>("GAME")->data;
	loadActions(gameData["actions"].get<std::vector<std::string>>());
	loadEnemies(gameData["enemies"].get<std::vector<std::string>>());
}

void Game::start(GameSettings settings)
{
	m_settings = settings;
	m_hero.init(m_assets->getAsset<Didax::DataAsset>("HERO")->data, this);
}

void Game::startActivity(const std::string& activityName)
{
	m_activeActivity = std::make_unique<Activity>(m_assets->getAsset<Didax::DataAsset>(activityName)->data, &m_hero, this);
}

Activity* Game::getActivity()
{
	return m_activeActivity.get();
}

bool Game::activityFinished() const
{
	if (m_activeActivity == nullptr)
		return true;
	return m_activeActivity->finished();
}

void Game::endActivity()
{
	m_activeActivity = nullptr;
}

Enemy* Game::getEnemy(const std::string& name)
{
	return m_allEnemies[name].get();
}

Action* Game::getAction(const std::string& name)
{
	return m_allActions[name].get();
}

void Game::loadActions(const std::vector<std::string>& aNames)
{
	for (auto& x : aNames)
		m_allActions.emplace(x, std::make_unique<Action>(m_assets->getAsset<Didax::DataAsset>(x)->data, x, this));
}

void Game::loadEnemies(const std::vector<std::string>& aNames)
{
	for (auto& x : aNames)
		m_allEnemies.emplace(x, std::make_unique<Enemy>(m_assets->getAsset<Didax::DataAsset>(x)->data, x));
}
