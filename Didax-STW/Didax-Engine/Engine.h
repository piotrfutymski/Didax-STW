#pragma once

#include <type_traits>

#include "Entity.h"
#include "Window.h"
#include "Input.h"
#include "AssetManager.h"

namespace Didax
{

    typedef Entity* Entity_ptr;

    class Engine
    {
    public:

        using EntityHolder_t = std::unordered_map<std::string, std::unique_ptr<Entity>>;
        using EntityPriorityMap_t = std::vector<std::string>;

        //

        Engine();

        Engine(const std::string& dataFilePath);

        bool init(const std::string& dataFilePath);

        void run();

        void setOwnCursor(const std::string& def, const std::string& hand, const std::string& load);

        //

        Entity_ptr addEntity();

        Entity_ptr addEntity(const std::string& name);

        Entity_ptr getEntity(const std::string& name);

        Entity_ptr removeEntity(const std::string& name);

        //

        float getDeltaTime()const;

        void setCameraPosition(float x, float y);

        void setCameraPosition(const sf::Vector2f & p);

        void moveCamera(const sf::Vector2f& d);

        sf::Vector2f getCameraPosition()const;

        void setCameraSize(float w, float h);

        void setCameraSize(const sf::Vector2f& p);

        sf::Vector2f getCameraSize()const;

        //
        

        template<typename T, typename... Args>
        Entity_ptr addEntity(const std::string& name, Args&&... args)
        {
            m_entities[name] = std::move(std::make_unique<Entity>(this, name));
            m_entitiesAdded.push_back(name);
            m_entities[name]->addScript<T>(std::forward<Args>(args)...);
            return m_entities[name].get();
        }

        template<typename T>
        Entity_ptr addEntity()
        {
            return addEntity<T>(getNextName());
        }

        AssetManager* getAssets();

        void sortEntities();

        void close();

    private:

        std::string m_dataFilePath;
        nlohmann::json m_settings;

        EntityHolder_t m_entities;
        EntityPriorityMap_t m_priortyQueue;

        float m_deltaT{ 0.0f };
        float debClock{ 1.0f };

        sf::Clock m_clock;
        Window m_window;
        AssetManager m_assets;

        size_t ID{ 0 };

        std::vector<std::string> m_entitiesAdded{};

        bool m_ownCursor{ false };
        bool m_close{ false };

    private:

        bool loadSettings();

        bool createWindow();

        bool loadAssets();

        void input();

        void update();

        void render();

        std::string getNextName();

    };

}

