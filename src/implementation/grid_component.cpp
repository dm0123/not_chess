#include <grid_component.hpp>

namespace not_chess
{

void GridRenderable::Init()
{
    for(int i = 0; i < 8; ++i)
    {
        auto is_black = i % 2 == 0;
        for( int j = 0; j < 8; ++j)
        {
            auto& rect = m_rectangles[j + (i*8)];
            rect.setPosition(j*64.f, i*64.f);
            rect.setSize(sf::Vector2f(64.f, 64.f));
            rect.setFillColor(is_black ? sf::Color::Blue : sf::Color::Cyan);
            is_black = !is_black;
        }
    }
}

void GridRenderable::Draw(sf::RenderWindow& window, sf::Vector2i /*position*/)
{
    for(auto& rect : m_rectangles)
        window.draw(rect);
}

} // namespace not_chess
