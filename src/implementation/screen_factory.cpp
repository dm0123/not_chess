#include <screen_factory.hpp>
#include <game_screen.hpp>
#include <pause_screen.hpp>
#include <finished_screen.hpp>
#include <game.hpp>

namespace not_chess
{
void GameScreensFactory::Init()
{
    MakeGameScreen();
    MakePauseScreen();
    MakeFinishedScreen();
}

void GameScreensFactory::MakeFinishedScreen()
{
    std::unique_ptr<core::Screen> screen = std::make_unique<core::Screen>();
    screen->AddEntity(m_game.m_data.winner_text);
    m_game.AddScreen(std::move(screen));
}

void GameScreensFactory::MakeGameScreen()
{
    std::unique_ptr<GameScreen> screen = std::make_unique<GameScreen>();
    screen->SetGame(&m_game);
    screen->AddEntity(m_game.m_data.board);
    screen->AddEntities(m_game.m_data.black_pawns);
    screen->AddEntities(m_game.m_data.white_pawns);
    screen->AddEntity(m_game.m_data.your_turn_text);
    screen->AddEntity(m_game.m_data.general_info_text);

    m_game.AddScreen(std::move(screen));
}

void GameScreensFactory::MakePauseScreen()
{
    std::unique_ptr<PauseScreen> screen = std::make_unique<PauseScreen>();
    screen->AddEntity(m_game.m_data.paused_text);
    screen->SetGame(&m_game);
    m_game.AddScreen(std::move(screen));
}

void GameScreensFactory::MakeSettingsScreen()
{
    std::unique_ptr<core::Screen> screen = std::make_unique<core::Screen>();
    m_game.AddScreen(std::move(screen));
}
} // namespace not_chess
