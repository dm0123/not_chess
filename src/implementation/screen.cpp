#include <core/screen.hpp>
#include <entity.hpp>
#include <component.hpp>
#include <memory>

namespace not_chess::core
{
void SimpleSpriteItem::Draw(sf::RenderWindow& window, sf::Vector2i position)
{
    m_sprite.setPosition(position.x, position.y);
    window.draw(m_sprite);
}

void Screen::AddEntity(EntityId e)
{
    m_entities.push_back(e);
}

void Screen::AddEntities(const std::vector<EntityId>& entities)
{
    for(EntityId e : entities)
        AddEntity(e);
}

void Screen::Draw(sf::RenderWindow& window)
{
    for(EntityId entity : m_entities)
    {
        auto const& e = ECSManager::Instance().Get(entity);
        for(std::unique_ptr<AbstractComponent> const& component_ptr : e.Components())
        {
            auto const& drawables = component_ptr->GetDrawables();
            for(auto drawable : drawables)
                drawable->Draw(window, e.GetPosition());
        }
    }
}

} // namespace not_chess::core
