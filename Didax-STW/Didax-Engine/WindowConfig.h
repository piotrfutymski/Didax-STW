#pragma once

#include <SFML/Window.hpp>
#include <nlohmann/json.hpp>

namespace Didax
{

	class WindowConfig
	{
	public:
		WindowConfig();

		bool init(const nlohmann::json& j);

		bool loadFromJson(const nlohmann::json& j);

		sf::VideoMode m_mode;
		sf::Uint32 m_windowStyle;
		int m_framerateLimit;

	};

}
