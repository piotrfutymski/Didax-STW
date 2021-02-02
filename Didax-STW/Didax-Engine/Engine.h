#pragma once

#include <type_traits>

#include "Entity.h"
#include "Window.h"
#include "Input.h"
#include "AssetManager.h"

namespace Didax
{

    typedef std::weak_ptr<Entity> Entity_ptr;

    class Engine
    {
    public:

        using EntityHolder_t = std::unordered_map<std::string, std::shared_ptr<Entity>>;
        using EntityPriorityMap_t = std::map<int, std::string>;

        //

        Engine();

        Engine(const std::string& dataFilePath);

        void init(const std::string& dataFilePath);

        bool run();

        //

        Entity_ptr addEntity();

        Entity_ptr addEntity(const std::string& name);

        Entity_ptr getEntity(const std::string& name);

        Entity_ptr removeEntity(const std::string& name);

        //

        float getDeltaTime()const;

        void setCameraPosition(float x, float y);

        void setCameraPosition(const sf::Vector2f & p);

        sf::Vector2f getCameraPosition()const;

        void setCameraSize(float w, float h);

        void setCameraSize(const sf::Vector2f& p);

        sf::Vector2f getCameraSize()const;    

    private:

        std::string m_dataFilePath;
        nlohmann::json m_settings;

        EntityHolder_t m_entities;
        EntityPriorityMap_t m_priortyQueue;

        float m_deltaT{ 0.0 };

        sf::Clock m_clock;
        Window m_window;
        AssetManager m_assets;

    private:

        bool loadSettings();

        bool createWindow();

        bool loadAssets();

        void input();

        void update();

        void render();

    };

}

