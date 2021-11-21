#pragma once
#include <component.hpp>
#include <core/screen.hpp>
#include <string_view>

namespace not_chess
{
using namespace std::literals;

class GridRenderable : public core::IDrawable
{
public:
    GridRenderable() = default;

    void Init();
    void Draw(sf::RenderWindow& window, sf::Vector2i position) override;
private:
    std::array<sf::RectangleShape, 8 * 8> m_rectangles;
};

class GridComponent : public AbstractComponent
{
public:
    void Init() override
    {
        m_grid.Init();
        m_drawables.push_back(&m_grid);
    }

    std::string_view Name() override { return "grid"sv; }
private:
    GridRenderable m_grid;
};
} // namespace not_chess
