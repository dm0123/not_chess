#include <core/input.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Touch.hpp>
#include <unordered_map>

namespace not_chess::core
{
Input::Input() : m_window_event_handler([this](sf::Event ev){ Process(ev); })
{
}

void Input::Process(sf::Event const& event)
{
    switch(event.type)
    {
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Key::Space)
            m_pressed_event(Key::Space);
        else if(event.key.code == sf::Keyboard::Key::Escape)
            m_pressed_event(Key::Esc);
        else if(event.key.code == sf::Keyboard::Key::Left)
            m_pressed_event(Key::Left);
        else if(event.key.code == sf::Keyboard::Key::Right)
            m_pressed_event(Key::Right);
        else if(event.key.code == sf::Keyboard::Key::Up)
            m_pressed_event(Key::Up);
        else if(event.key.code == sf::Keyboard::Key::Down)
            m_pressed_event(Key::Down);
        else if(event.key.code == sf::Keyboard::Key::W)
            m_pressed_event(Key::W);
        else if(event.key.code == sf::Keyboard::Key::A)
            m_pressed_event(Key::A);
        else if(event.key.code == sf::Keyboard::Key::S)
            m_pressed_event(Key::S);
        else if(event.key.code == sf::Keyboard::Key::D)
            m_pressed_event(Key::D);
        break;
    case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::Key::Space)
            m_released_event(Key::Space);
        else if(event.key.code == sf::Keyboard::Key::Escape)
            m_released_event(Key::Esc);
        else if(event.key.code == sf::Keyboard::Key::Left)
            m_released_event(Key::Left);
        else if(event.key.code == sf::Keyboard::Key::Right)
            m_released_event(Key::Right);
        else if(event.key.code == sf::Keyboard::Key::Up)
            m_released_event(Key::Up);
        else if(event.key.code == sf::Keyboard::Key::Down)
            m_released_event(Key::Down);
        else if(event.key.code == sf::Keyboard::Key::W)
            m_released_event(Key::W);
        else if(event.key.code == sf::Keyboard::Key::A)
            m_released_event(Key::A);
        else if(event.key.code == sf::Keyboard::Key::S)
            m_released_event(Key::S);
        else if(event.key.code == sf::Keyboard::Key::D)
            m_released_event(Key::D);
        break;
    default:
        break;
    }
}

void Input::AddPressedEventHandler(EventHandler<Key> ev_handler) noexcept
{
    m_pressed_event += ev_handler;
}

void Input::AddReleasedEventHandler(EventHandler<Key> ev_handler) noexcept
{
    m_released_event += ev_handler;
}

const EventHandler<sf::Event>& Input::GetWindowEventHandler() const noexcept
{
    return m_window_event_handler;
}
} // namespace not_chess::core
