#pragma once
#include <vector>
#include <string>
#include <array>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include <component.hpp>

namespace not_chess::core
{
class IDrawable
{
public:
    IDrawable() = default;

    void SetPosition(sf::Vector2i pos) { m_screen_pos = pos; }

    virtual ~IDrawable() = default;
    virtual void Draw(sf::RenderWindow& window, sf::Vector2i position) {}
protected:
    sf::Vector2i m_screen_pos;
};


class SimpleSpriteItem : public IDrawable
{
public:
    SimpleSpriteItem() = default;
    void Draw(sf::RenderWindow& window, sf::Vector2i position) override;
    void SetSprite(sf::Sprite const& sprite) noexcept { m_sprite = sprite; }
private:
    sf::Sprite m_sprite;
};

class Screen
{
public:
    Screen();
    ~Screen();

    void AddEntity(EntityId e);
    void AddEntities(std::vector<EntityId> const& entities);
    void Draw(sf::RenderWindow& window);
protected:
    std::vector<EntityId> m_entities;
};
} // namespace not_chess::core
