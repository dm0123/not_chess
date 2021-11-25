#pragma once
#include <core/screen.hpp>
#include <core/events.hpp>
#include <core/input.hpp>
#include <entity.hpp>

#include <optional>

namespace not_chess
{
class Game;

class GameScreen : public core::Screen
{
public:

    enum class InputMode
    {
        Choosing,
        Moving
    };

    struct PlayerInputMode
    {
        InputMode mode = InputMode::Choosing;
        void Next() noexcept
        {
            if(mode == InputMode::Choosing)
                mode = InputMode::Moving;
            else mode = InputMode::Choosing;
        }
    };

    GameScreen();

    void SetGame(Game* game) { m_game = game; }
    void OnInput(core::Input::Key key) override;
    void Update() override;

    void MoveCursor(core::Input::Key key);
    void PlayerMovePawn(core::Input::Key key);
    void CheckWinCondition();
    EntityId FindActivePawn();
private:
    Game* m_game = nullptr;
    PlayerInputMode input_mode;
    std::optional<sf::Vector2i> active_tile;
    sf::Vector2i cursor_tile {0, 0};
};
} // namespace not_chess
