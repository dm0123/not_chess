#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <core/events.hpp>
#include <core/screen.hpp>

namespace not_chess::core
{
class App
{
public:
    struct Options
    {
        Options() : width(900), height(900), window_title("Not Chess")
        {
        }

        int width;
        int height;
        std::string window_title;
    };

    void Init(Options opts = {});
    void Run();
    void Shutdown();

    void AddFinishedEventHandler(EventHandler<> const& ev) noexcept;
    void AddWindowEventHandler(EventHandler<sf::Event> const& ev) noexcept;
    void AddDrawEventHandler(EventHandler<> const& ev) noexcept;
    sf::RenderWindow& Window() noexcept { return m_window; }
private:
    sf::RenderWindow m_window;
    Options m_options;

    core::Event<> m_finished_event;
    core::Event<sf::Event> m_window_event;
    core::Event<> m_draw_event;
};

} // namespace not_chess::core
