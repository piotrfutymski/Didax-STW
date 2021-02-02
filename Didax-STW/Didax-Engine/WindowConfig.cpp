#include "WindowConfig.h"

Didax::WindowConfig::WindowConfig():m_mode { 640, 480 }, m_windowStyle{ sf::Style::Default }, m_framerateLimit{ 60 }
{
}

bool Didax::WindowConfig::init(const nlohmann::json& j)
{
	return loadFromJson(j);
}

bool Didax::WindowConfig::loadFromJson(const nlohmann::json& j)
{
	try{
		auto windSet = j["windowSettings"];
		m_mode.width = windSet["videoModeWidth"];
		m_mode.height = windSet["videoModeHeight"];
		m_windowStyle = windSet["windowStyle"];
	}catch (const std::exception& ){
		return false;
	}
	return true;
}
