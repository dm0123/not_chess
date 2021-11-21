#pragma once
#include <core/screen.hpp>
#include <core/events.hpp>

#include <vector>
#include <memory>

#include <SFML/System/Vector2.hpp>
#include <component.hpp>

namespace not_chess
{
class Entity;

/// Class for storing all entities and its components
class ECSManager
{
public:
    static ECSManager& Instance();
    void Init();

    EntityId MakeEntity(std::string name, std::vector<std::unique_ptr<AbstractComponent>>&& components);
    Entity& Get(EntityId id);
    Entity& FindByName(std::string_view name);
    void AddComponent(EntityId id, std::unique_ptr<AbstractComponent>&& c);
    std::unique_ptr<AbstractComponent>& ComponentByName(EntityId id, std::string_view name);

    core::EventHandler<> const& TickListener() const noexcept { return m_game_tick_handler; }

    std::vector<core::IDrawable*> CollectDrawables(EntityId e_id);
private:
    ECSManager();
    // we may implement some sort of pool here
    // or just use entt library as underlying entity manager
    std::vector<Entity> m_entities;
    std::unordered_map<std::string, EntityId> m_entities_by_name;
    core::EventHandler<> m_game_tick_handler;
};

class Entity
{
    friend class ECSManager;
public:
    Entity(std::string name);
    Entity(Entity const& other) = default;
    Entity(Entity&& other) = default;

    std::vector<std::unique_ptr<AbstractComponent>> const& Components() const { return m_components; }
    void AddComponent(std::unique_ptr<AbstractComponent>&& c);

    std::string_view Name() const noexcept { return m_name; }
    void SetPosition(sf::Vector2i const& pos) noexcept { m_screen_pos = pos; }
    sf::Vector2i GetPosition() const noexcept { return m_screen_pos; }

    ~Entity();
private:
    Entity();

    std::string m_name;
    std::vector<std::unique_ptr<AbstractComponent>> m_components;
    sf::Vector2i m_screen_pos;
};
} // namespace not_chess::core
