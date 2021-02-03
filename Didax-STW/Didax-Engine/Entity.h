#pragma once

#include "Script.h"
#include "VoidScript.h"
#include "Canvas.h"

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
		void init(Args&&...args)
		{
			std::unique_ptr<Script<GameObject>> scr = std::make_unique<Script<GameObject>>(m_parent);
			scr->init(std::forward<Args>(args)...);
			m_script = std::move(scr);
		}

		template<typename T>
		typename std::enable_if<std::is_base_of<Widget, T>::value, T>::type* createWidget()
		{
			m_widget = std::make_unique<T>(m_assets);
			return static_cast<T*> (m_widget.get());
		}

		template<typename T>
		typename std::enable_if<std::is_base_of<Widget, T>::value, T>::type* getWidget()
		{
			if (m_widget == nullptr)
				return nullptr;
			return static_cast<T*>(m_widget.get());
		}

		void removeWidget();

		template<typename T>
		Script<T>* getScript()
		{
			if (m_script == nullptr)
				return nullptr;
			return static_cast<Script<T>*>(m_script.get());
		}


		bool getToKill()const;
		void setToKill();

		bool isVisible()const;
		void setVisible(bool v);

		int getPriority()const;
		void setPrority(int p);

		bool isActive()const;
		void setActive(bool a);

		std::string getName()const;

	private:

		Engine* m_parent;
		std::string m_name;
		AssetManager* m_assets;

		std::unique_ptr<Script_t> m_script{ nullptr };
		std::unique_ptr<Widget> m_widget{ nullptr };

		bool m_isVisible{ true };
		int m_priority{ 0 };
		bool m_isActive{ true };
		bool m_toKill{ false };
		

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	};

}

