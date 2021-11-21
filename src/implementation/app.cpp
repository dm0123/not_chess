#include <core/app.hpp>
#include <SFML/Graphics.hpp>

namespace not_chess::core
{
void App::Init(Options opts)
{
    m_options = opts;
    m_window.create(sf::VideoMode(opts.width, opts.height), opts.window_title);
}

void App::Run()
{
    if(!m_window.isOpen())
        // Notify subscribers app window is closed
        m_finished_event();
    sf::Event event;
    while(m_window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
            m_window.close();
        // Notify all window event subscibers
        m_window_event(event);
    }
    m_window.clear(sf::Color::Blue);
    // Notify all draw event subscribers to draw
    m_draw_event();

    m_window.display();
}

void App::Shutdown()
{
}

void App::AddFinishedEventHandler(const EventHandler<>& ev) noexcept
{
    m_finished_event += ev;
}

void App::AddWindowEventHandler(const EventHandler<sf::Event>& ev) noexcept
{
    m_window_event += ev;
}

void App::AddDrawEventHandler(const EventHandler<>& ev) noexcept
{
    m_draw_event += ev;
}
} // not_chess::core
