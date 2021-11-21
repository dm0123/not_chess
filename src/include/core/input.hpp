#pragma once
#include "events.hpp"
#include <SFML/Window/Event.hpp>

namespace not_chess::core
{
/// Input handling via events
class Input
{
public:
    /// Enum only for input of our interest
    enum class Key
    {
        Space,
        LeftMouse,
        Esc,
        Touch,
        Left,
        Up,
        Down,
        W, A, S, D
    };

    Input();
    ~Input() = default;

    /// Main processing function
    void Process(sf::Event const& event);

    void AddPressedEventHandler(EventHandler<Key> ev_handler) noexcept; // TODO: make coordinates for UI
    void AddReleasedEventHandler(EventHandler<Key> ev_handler) noexcept;
    EventHandler<sf::Event> const& GetWindowEventHandler() const noexcept;
private:
    Event<Key> m_pressed_event;
    Event<Key> m_released_event;
    EventHandler<sf::Event> m_window_event_handler;
};
} // namespace not_chess::core
