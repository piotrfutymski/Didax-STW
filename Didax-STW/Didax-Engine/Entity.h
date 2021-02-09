#pragma once

#include "Script.h"
#include "VoidScript.h"
#include "WidgetJsonLoader.h"

namespace Didax
{

class Engine;

	class Entity : public sf::Drawable
	{
	public:

		Entity(Engine* parent, const std::string& name);


		void update(float dT);
		void input(const sf::Event& evt);
		void kill();
		void start();

		template<typename GameObject, typename... Args>
		void addScript(Args&&...args)
		{
			std::unique_ptr<Script<GameObject>> scr = std::make_unique<Script<GameObject>>(m_parent);
			scr->init(std::forward<Args>(args)...);
			m_script = std::move(scr);
			if constexpr (detail::has_setMe<GameObject, void(Entity*)>::value)
				getScript<GameObject>()->setMe(this);
			start();
		}

		template<typename T>
		typename std::enable_if<std::is_base_of<Widget, T>::value, T>::type* createWidget()
		{
			m_widget = std::make_unique<T>(m_assets, this);
			return static_cast<T*> (m_widget.get());
		}

		Widget * createWidget(const std::string& name, int priority = 0);

		template<typename T>
		typename std::enable_if<std::is_base_of<Widget, T>::value, T>::type* getWidget()
		{
			if (m_widget == nullptr)
				return nullptr;
			return static_cast<T*>(m_widget.get());
		}

		Widget* getWidget()
		{
			if (m_widget == nullptr)
				return nullptr;
			return m_widget.get();
		}

		void removeWidget();

		template<typename T>
		T* getScript()
		{
			if (m_script == nullptr)
				return nullptr;
			return static_cast<Script<T>*>(m_script.get())->getGameObject();
		}


		bool getToKill()const;
		void setToKill();

		int getPriority()const;
		void setPriority(int p);

		std::string getName()const;

	private:

		Engine* m_parent;
		std::string m_name;
		AssetManager* m_assets;

		std::unique_ptr<Script_t> m_script{ nullptr };
		std::unique_ptr<Widget> m_widget{ nullptr };

		int m_priority{ 0 };
		bool m_toKill{ false };
		

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};

}

