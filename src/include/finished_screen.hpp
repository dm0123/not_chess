#pragma once
#include <core/screen.hpp>
#include <core/input.hpp>

namespace not_chess
{
class Game;

class FinishedScreen : public core::Screen
{
public:
    void Update() override;
    void SetGame(Game* game) noexcept { m_game = game; }
    void OnInput(core::Input::Key key) override;
private:
    Game* m_game = nullptr;
};
} // namespace not_chess
