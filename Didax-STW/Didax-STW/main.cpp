#include "RootFrame.h"
#include "Activity.h"

class TestFrame : public RootFrame
{
public:

	virtual void _onUpdate(Didax::Engine* e) override
	{
	}

	virtual void _onStart(Didax::Engine* e) override
	{
	}

	virtual void _onKill(Didax::Engine* e) override
	{
		e->close();
	}
};


int main()
{
	Didax::Engine e("data/settings.json");
	Enemy en;
	Hero h;
	std::vector<Action> actions;
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("quickThrustACT")->data, L"quickThrustACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("bloodyBlowACT")->data, L"bloodyBlowACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("straightCutACT")->data, L"straightCutACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("parryACT")->data, L"parryACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("dodgeACT")->data, L"dodgeACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("takingTheBlowACT")->data, L"takingTheBlowACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("earthPostureACT")->data, L"earthPostureACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("firePostureACT")->data, L"firePostureACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("backToPositionACT")->data, L"backToPositionACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("tauntACT")->data, L"tauntACT"));
	actions.push_back(Action(e.getAssets()->getAsset<Didax::DataAsset>("takeABreathACT")->data, L"takeABreathACT"));
	for (auto& x : actions)
		h.getActions().push_back(&x);
	Activity activity(&h, &en);
	while (true)
	{
		activity.startTurn();
		std::cout << "Poczarek tury:" << "\n";
		std::cout << "Akcje do wyboru (napisz numery wybranych):" << "\n";
		int i = 0;
		for (auto a : activity.getOnHandActions())
		{
			i++;
			std::wcout << std::to_wstring(i) + L": " + a->getName()<<std::endl;
		}
		i = 0;
		int nums[4];
		for (int i = 0; i < 4; i++)
		{
			std::cin >> nums[i];
			activity.setOnBoard(nums[i]-1, i);
		}
		std::cout << "Na bordzie sa:\n";
		for (auto a : activity.getOnBoardActions())
		{
			i++;
			std::wcout << std::to_wstring(i) + L": " + a->getName() << std::endl;
		}
		for (int i = 0; i < 4; i++)
		{
			auto res = activity.playAction(i);
			std::cout << "Adder for "<<i<< " action:\t" << res.first << "\t" << res.second << "\t" << res.third << "\n";
		}
		auto pasek = activity.getStatus();
		std::cout<<"Po dodatkach mamy   :\t" << pasek.first << "\t" << pasek.second << "\t" << pasek.third << "\n";
		for (int i = 0; i < 4; i++)
		{
			auto res = activity.playBonus(i);
			std::cout << "Bonus for " << i << " action:\t" << res.first << "\t" << res.second << "\t" << res.third << "\n";
		}
		pasek = activity.getStatus();
		std::cout << "Po bonusach mamy   :\t" << pasek.first << "\t" << pasek.second << "\t" << pasek.third << "\n";
		activity.playEnemy();
		auto res = activity.geEnemyRemovedStatus();
		std::cout << "Wilk uderza za    \t" <<  res.first << "\t" << res.second << "\t" << res.third << "\n";
		pasek = activity.getStatus();
		std::cout<< "Ostatecznie mamy:\t" << pasek.first << "\t" << pasek.second << "\t" << pasek.third << "\n";
	}



	//e.setOwnCursor("arrowCUR", "handCUR", "loadingCUR");
	//e.addEntity<TestFrame>("testWIDG");
	//e.run();
}