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

Screen::Screen() = default;

Screen::~Screen() = default;

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
                if(drawable->Visible())
                    drawable->Draw(window, e.GetPosition());
        }
    }
}

TextItem::TextItem() = default;

void TextItem::Draw(sf::RenderWindow& window, sf::Vector2i position)
{
    m_text.setPosition(position.x, position.y);
    m_text.setScale(0.9, 0.9);
    m_text.setLetterSpacing(1.2f);
    window.draw(m_text);
}

} // namespace not_chess::core
