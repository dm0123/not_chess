#include <screen_factory.hpp>
#include <game.hpp>

namespace not_chess
{
void GameScreensFactory::Init()
{
    MakeGameScreen();
    MakePauseScreen();
    MakeMainMenuScreen();
}

void GameScreensFactory::MakeMainMenuScreen()
{
    std::unique_ptr<core::Screen> screen = std::make_unique<core::Screen>();
    m_game.AddScreen(std::move(screen));
}

void GameScreensFactory::MakeGameScreen()
{
    std::unique_ptr<core::Screen> screen = std::make_unique<core::Screen>();
    screen->AddEntity(m_game.m_data.board);
    screen->AddEntities(m_game.m_data.black_pawns);
    screen->AddEntities(m_game.m_data.white_pawns);
    m_game.AddScreen(std::move(screen));
}

void GameScreensFactory::MakePauseScreen()
{
    std::unique_ptr<core::Screen> screen = std::make_unique<core::Screen>();
    m_game.AddScreen(std::move(screen));
}

void GameScreensFactory::MakeSettingsScreen()
{
    std::unique_ptr<core::Screen> screen = std::make_unique<core::Screen>();
    m_game.AddScreen(std::move(screen));
}
} // namespace not_chess
