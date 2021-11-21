#pragma once
#include <core/screen.hpp>

namespace not_chess
{
class Game;
/// Helper for making various game screens
class GameScreensFactory
{
public:
    GameScreensFactory(Game const& g) : m_game(g)
    {
    }

    ~GameScreensFactory() = default;

    core::Screen MakeMainMenuScreen();
    core::Screen MakeGameScreen();
    core::Screen MakePauseScreen();
    core::Screen MakeSettingsScreen();
private:
    Game const& m_game;
};
}
