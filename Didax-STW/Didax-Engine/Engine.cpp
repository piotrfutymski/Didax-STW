#include "Engine.h"

Didax::Engine::Engine()
{
}

Didax::Engine::Engine(const std::string& dataFilePath)
{
}

int Didax::Engine::init(const std::string& dataFilePath)
{
	return 0;
}

void Didax::Engine::run()
{
}

Didax::Entity_ptr Didax::Engine::addEntity()
{
	return Entity_ptr();
}

Didax::Entity_ptr Didax::Engine::addEntity(const std::string& name)
{
	return Entity_ptr();
}

Didax::Entity_ptr Didax::Engine::getEntity(const std::string& name)
{
	return Entity_ptr();
}

Didax::Entity_ptr Didax::Engine::removeEntity(const std::string& name)
{
	return Entity_ptr();
}

float Didax::Engine::getDeltaTime() const
{
	return 0.0f;
}

void Didax::Engine::setCameraPosition(float x, float y)
{
}

void Didax::Engine::setCameraPosition(const sf::Vector2f& p)
{
}

sf::Vector2f Didax::Engine::getCameraPosition() const
{
	return sf::Vector2f();
}

void Didax::Engine::setCameraSize(float w, float h)
{
}

void Didax::Engine::setCameraSize(const sf::Vector2f& p)
{
}

sf::Vector2f Didax::Engine::getCameraSize() const
{
	return sf::Vector2f();
}
