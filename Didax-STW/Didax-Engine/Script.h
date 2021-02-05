#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "HasMember.h"

namespace Didax
{
	class Engine;

	class Script_t
	{
	public:

	virtual void update(float dt) = 0;

	virtual void input(const sf::Event& evt) = 0;

	virtual void kill() = 0;

	virtual void start() = 0;

	};

	template<typename T>
	class Script : public Script_t
	{
	public:

		Script(Engine* e): m_parent(e)
		{
		}

		template<typename... Args>
		void init(Args&&... args)
		{
			m_gameObject = std::make_unique<T>(std::forward<Args>(args)...);
		}

		virtual void start() override
		{
			if constexpr (detail::has_onStart<T, void(Engine*)>::value)
				m_gameObject->onStart(m_parent);
		}

		virtual void kill() override
		{
			if constexpr (detail::has_onKill<T, void(Engine*)>::value)
				m_gameObject->onKill(m_parent);
		}

		virtual void update(float dt) override
		{
			if constexpr (detail::has_onUpdate<T, void(Engine*)>::value)
				m_gameObject->onUpdate(m_parent);
		}

		virtual void input(const sf::Event& evt) override
		{
			if constexpr (detail::has_onInput<T, void(Engine*, const sf::Event&)>::value)
				m_gameObject->onInput(m_parent, evt);
		}

		T* getGameObject()
		{
			return m_gameObject.get();
		}

		const T* getGameObject()const
		{
			return m_gameObject.get();
		}

	protected:

	private:

		std::unique_ptr<T> m_gameObject;

		Engine* m_parent;

	};

}



