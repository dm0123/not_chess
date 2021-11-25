#pragma once
#include <vector>
#include <string>
#include <array>

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

#include <component.hpp>
#include <core/input.hpp>

namespace not_chess::core
{
class IDrawable
{
public:
    IDrawable() = default;

    void SetPosition(sf::Vector2i pos) { m_screen_pos = pos; }

    virtual ~IDrawable() = default;
    virtual void Draw(sf::RenderWindow& window, sf::Vector2i position) {}
    bool Visible() const noexcept { return m_visible; }
    void SetVisible(bool is_visible) noexcept { m_visible = is_visible; }
protected:
    sf::Vector2i m_screen_pos;
    bool m_visible = true;
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

class TextItem : public IDrawable
{
public:
    TextItem();
    void SetText(sf::Text const& t) noexcept { m_text = t; }
    void SetString(std::string_view text) noexcept { m_text.setString(sf::String(text.data())); }
    void Draw(sf::RenderWindow& window, sf::Vector2i position) override;
private:
    sf::Text m_text;
};

class Screen
{
public:
    Screen();
    ~Screen();

    void AddEntity(EntityId e);
    void AddEntities(std::vector<EntityId> const& entities);
    void Draw(sf::RenderWindow& window);

    virtual void Update() {}
    virtual void OnInput(core::Input::Key key) {}
protected:
    std::vector<EntityId> m_entities;
};
} // namespace not_chess::core
