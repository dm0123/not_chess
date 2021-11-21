#include <screen_factory.hpp>
#include <game.hpp>

namespace not_chess
{
core::Screen GameScreensFactory::MakeMainMenuScreen()
{
    core::Screen screen;
    return screen;
}

core::Screen GameScreensFactory::MakeGameScreen()
{
    core::Screen screen;
    screen.AddEntity(m_game.m_data.board);
    screen.AddEntities(m_game.m_data.black_pawns);
    screen.AddEntities(m_game.m_data.white_pawns);
    return screen;
}

core::Screen GameScreensFactory::MakePauseScreen()
{
    core::Screen screen;
    return screen;
}

core::Screen GameScreensFactory::MakeSettingsScreen()
{
    core::Screen screen;
    return screen;
}
} // namespace not_chess
