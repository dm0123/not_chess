#include <finished_screen.hpp>
#include <text_component.hpp>
#include <game.hpp>

namespace not_chess
{
void FinishedScreen::Update()
{
    if(m_game)
    {
        TextComponent* comp = ECSManager::Instance().GetComponent<TextComponent>(m_game->Data().winner_text, "text");
        if(comp)
        {
            if(m_game->Data().player_won)
                comp->SetString("Winner is human.");
            else
                comp->SetString("Winner is AI.");
        }
    }
}

void FinishedScreen::OnInput(core::Input::Key key)
{
    if(key == core::Input::Key::Esc)
    {
        m_game->Reset();
    }
}
} // namespace not_chess
