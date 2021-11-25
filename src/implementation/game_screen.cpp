#include <game_screen.hpp>
#include <game.hpp>
#include <entity.hpp>
#include <grid_component.hpp>
#include <position_component.hpp>
#include <text_component.hpp>

namespace not_chess
{
using namespace std::literals;

GameScreen::GameScreen() = default;

void GameScreen::Update()
{
    TextComponent* text = ECSManager::Instance().GetComponent<TextComponent>(m_game->Data().your_turn_text, "text"sv);
    if(!text)
        return;
    if(m_game->Data().player_turn)
        text->SetVisible(true);
    else
        text->SetVisible(false);
}

void GameScreen::OnInput(core::Input::Key key)
{
    if(key == core::Input::Key::Esc && m_game->CurrentState() == Game::State::Playing)
        m_game->OnStateChange(Game::State::Paused);

    if(m_game->CurrentState() != Game::State::Playing)
        return;

    auto& game_data = m_game->Data();
    // not player turn yet
    if(!game_data.player_turn)
        return;

    // react to player input
    if(key == core::Input::Key::Space)
        input_mode.Next();
    else if(input_mode.mode == InputMode::Choosing)
        MoveCursor(key);
    else if(input_mode.mode == InputMode::Moving)
        PlayerMovePawn(key);
}

void GameScreen::MoveCursor(core::Input::Key key)
{
    auto game_data = m_game->Data();
    switch(key)
    {
    case core::Input::Key::Left:
    case core::Input::Key::A:
        cursor_tile.x--;
        if(cursor_tile.x < 0)
            cursor_tile.x = 0;
        break;
    case core::Input::Key::Right:
    case core::Input::Key::D:
        cursor_tile.x++;
        if(cursor_tile.x > 7)
            cursor_tile.x = 7;
        break;
    case core::Input::Key::Up:
    case core::Input::Key::W:
        cursor_tile.y--;
        if(cursor_tile.y < 0)
            cursor_tile.y = 0;
        break;
    case core::Input::Key::Down:
    case core::Input::Key::S:
        cursor_tile.y++;
        if(cursor_tile.y > 7)
            cursor_tile.y = 7;
    default:
        break;
    }
    GridComponent* grid = ECSManager::Instance().GetComponent<GridComponent>(game_data.board, "grid");
    if(grid)
        grid->SetActiveTile(cursor_tile.x, cursor_tile.y);
}

void GameScreen::PlayerMovePawn(core::Input::Key key)
{
    auto& game_data = m_game->Data();
    EntityId pawn_id = FindActivePawn();
    if(pawn_id == INVALID_ENTITY)
        return;

    if(m_game->MovePawn(pawn_id, key))
    {
        input_mode.mode = InputMode::Choosing;
        game_data.player_turn = false;
    }
}

void GameScreen::CheckWinCondition()
{
    // TODO: refactor
    // Check if black won
    int black_won = 0;
    for(int i = 7; i >= 5; --i)
        for(int j = 7; j >= 5; --j)
        {
            bool is_black = false;
            if(m_game->PositionHasPawn(sf::Vector2i(j, i), is_black) && is_black)
                black_won++;
        }
    if(black_won == 9)
    {
        m_game->Data().player_won = false;
        m_game->OnStateChange(Game::State::Finished);
        return;
    }

    // check if white won
    int white_won = 0;
    for(int i = 2; i >= 0; --i)
        for(int j = 2; j >= 0; --j)
        {
            bool is_black = false;
            if(m_game->PositionHasPawn(sf::Vector2i(j, i), is_black) && !is_black)
                white_won++;
        }
    if(white_won == 9)
    {
        m_game->Data().player_won = true;
        m_game->OnStateChange(Game::State::Finished);
        return;
    }
}

EntityId GameScreen::FindActivePawn()
{
    auto& game_data = m_game->Data();
    auto it = std::find_if(game_data.white_pawns.begin(), game_data.white_pawns.end(), [this](EntityId pawn_id)
    {
        PositionComponent* pos = ECSManager::Instance().GetComponent<PositionComponent>(pawn_id, "position");
        if(pos)
            return pos->GetPosition().first == cursor_tile.x && pos->GetPosition().second == cursor_tile.y;
        return false;
    });
    if(it == game_data.white_pawns.end())
        return INVALID_ENTITY;
    return *it;
}
} // namespace not_chess
