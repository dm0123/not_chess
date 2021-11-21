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
    case sf::Event::MouseButtonPressed:
        if(event.mouseButton.button == sf::Mouse::Button::Left)
            m_pressed_event(Key::LeftMouse);
        break;
    case sf::Event::MouseButtonReleased:
        if(event.mouseButton.button == sf::Mouse::Button::Left)
            m_released_event(Key::LeftMouse);
        break;
    case sf::Event::KeyPressed:
        if(event.key.code == sf::Keyboard::Key::Space)
            m_pressed_event(Key::Space);
        else if(event.key.code == sf::Keyboard::Key::Escape)
            m_pressed_event(Key::Esc);
        break;
    case sf::Event::KeyReleased:
        if(event.key.code == sf::Keyboard::Key::Space)
            m_released_event(Key::Space);
        else if(event.key.code == sf::Keyboard::Key::Escape)
            m_released_event(Key::Esc);
        break;
    case sf::Event::TouchBegan:
        if(event.touch.finger == 0)
            m_pressed_event(Key::Touch);
        break;
    case sf::Event::TouchEnded:
        if(event.touch.finger == 0)
            m_released_event(Key::Touch);
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
