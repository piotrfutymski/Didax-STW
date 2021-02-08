#pragma once
#include <memory>
#include "Activity.h"
#include "GameSettings.h"
#include "Hero.h"

class Game
{
public:

	using ActionHolder_t = std::map<std::string, std::unique_ptr<Action>>;
	using EnemyHolder_t = std::map<std::string, std::unique_ptr<Enemy>>;

	void init(Didax::AssetManager * a);

	void start(GameSettings settings);

	void startActivity(const std::string& activityName);

	Activity* getActivity();

	bool activityFinished()const;

	void endActivity();

	Enemy* getEnemy(const std::string & name);
	Action* getAction(const std::string& name);


private:

	Didax::AssetManager* m_assets;

	GameSettings m_settings;

	ActionHolder_t m_allActions;
	EnemyHolder_t m_allEnemies;

	std::unique_ptr<Activity> m_activeActivity{ nullptr };

	Hero m_hero;
	

private:

	void loadActions(const std::vector<std::string>& aNames);
	void loadEnemies(const std::vector<std::string>& aNames);

};

