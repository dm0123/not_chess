#pragma once
#include <core/screen.hpp>

namespace not_chess
{
class Game;
/// Helper for making various game screens
class GameScreensFactory
{
public:
    GameScreensFactory(Game& g) : m_game(g)
    {
    }

    ~GameScreensFactory() = default;

    void Init();

    void MakeMainMenuScreen();
    void MakeGameScreen();
    void MakePauseScreen();
    void MakeSettingsScreen();
private:
    Game& m_game;
};
}
