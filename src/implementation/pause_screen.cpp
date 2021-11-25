#include <pause_screen.hpp>
#include <game.hpp>

namespace not_chess
{
void PauseScreen::OnInput(core::Input::Key key)
{
    if(key == core::Input::Key::Esc)
        m_game->OnStateChange(Game::State::Playing);
}
} // namespace not_chess
