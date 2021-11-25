#pragma once
#include <core/screen.hpp>

namespace not_chess
{
class Game;

class PauseScreen : public core::Screen
{
public:
    void SetGame(Game* game) { m_game = game; }
    void OnInput(core::Input::Key key) override;
private:
    Game* m_game = nullptr;

};
} // namespace not_chess
