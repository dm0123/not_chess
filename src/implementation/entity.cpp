#include <entity.hpp>
#include <core/app_exception.hpp>

namespace not_chess
{
ECSManager& ECSManager::Instance()
{
    static ECSManager instance;
    return instance;
}

void ECSManager::Init()
{
    for(auto& e : m_entities)
        for(auto& component_ptr : e.Components())
            if(component_ptr)
                component_ptr->Init();
}

EntityId ECSManager::MakeEntity(std::string name, std::vector<std::unique_ptr<AbstractComponent>>&& components)
{
    Entity new_e(std::move(name));
    EntityId new_id = m_entities.size();
    for(std::unique_ptr<AbstractComponent>& component : components)
    {
        component->SetParent(new_id);
        new_e.m_components.push_back(std::move(component));
    }
    m_entities_by_name[std::string{ new_e.Name() }] = new_id;
    m_entities.push_back(std::move(new_e));
    return new_id;
}

Entity& ECSManager::Get(EntityId id)
{
    if(id < m_entities.size())
        return m_entities[id];
    throw core::AppException("ECSManager: invalid entity id");
}

Entity& ECSManager::FindByName(std::string_view name)
{
    auto it = m_entities_by_name.find(std::string{ name });
    if(it == m_entities_by_name.end())
        throw core::AppException("ECSManager: Failed to find entity by id");
    return m_entities[it->second];
}

void ECSManager::AddComponent(EntityId id, std::unique_ptr<AbstractComponent>&& c)
{
    m_entities[id].AddComponent(std::move(c));
}

std::unique_ptr<AbstractComponent>& ECSManager::ComponentByName(EntityId id, std::string_view name)
{
    auto& e = Get(id);
    for(auto& component : e.m_components)
    {
        if(component->Name() == name)
            return component;
    }
    throw core::AppException("ECSManager: invalid component name");
}

std::vector<core::IDrawable*> ECSManager::CollectDrawables(EntityId e_id)
{
    std::vector<core::IDrawable*> result;
    if(e_id > m_entities.size())
        throw core::AppException("CollectDrawables: Wrong entity id");
    auto& e = m_entities[e_id];
    for(std::unique_ptr<AbstractComponent> const& component_ptr : e.m_components)
    {
        if(component_ptr && !component_ptr->GetDrawables().empty())
            result.insert(result.end(), component_ptr->GetDrawables().begin(),
                                          component_ptr->GetDrawables().end());
    }
    return result;
}

ECSManager::ECSManager() : m_game_tick_handler([this]()
                           {
                               for(Entity& e : m_entities)
                                   for(std::unique_ptr<AbstractComponent>& component_ptr : e.m_components)
                                       if(component_ptr)
                                           component_ptr->Update();
                           })
{
}

Entity::Entity() = default;

Entity::Entity(std::string name) : m_name(std::move(name))
{
}

void Entity::AddComponent(std::unique_ptr<AbstractComponent>&& c)
{
    m_components.push_back(std::move(c));
}

Entity::~Entity()
{
}
} // namespace not_chess
