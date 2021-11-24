#include <ai_component.hpp>
#include <position_component.hpp>
#include <game.hpp>
#include <array>

namespace not_chess
{
using namespace std::literals;

AiComponent::AiComponent()
{
    for(int i = 7; i >= 5; --i)
        for(int j = 7; j >= 5; --j)
            m_available_slots.push_back({j, i});
    m_current_target = m_available_slots.front();
    m_available_slots.pop_front();
}

void AiComponent::MakeTurn()
{
    if(!m_game)
        return;
    Game::GameData& data = m_game->Data();
    if(data.player_turn)
        return;

    ChoosePawn();

    PositionComponent* pawn_pos = ECSManager::Instance().GetComponent<PositionComponent>(m_current_pawn, "position");
    if(pawn_pos)
    {
        auto position = pawn_pos->GetPosition();
        std::array<std::pair<sf::Vector2i, core::Input::Key>, 4> possible_moves =
            { std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first -1 , position.second), core::Input::Key::Left},
              std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first + 1, position.second), core::Input::Key::Right},
              std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first , position.second -1 ), core::Input::Key::Up},
              std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first , position.second + 1 ), core::Input::Key::Down}};


        auto& best_move = possible_moves[0];
        int best_diff_x = m_current_target.first - best_move.first.x;
        int best_diff_y = m_current_target.second - best_move.first.y;
        int possible_moves_count = 0;

        for(auto& possible_move_pos : possible_moves)
        {
            if(possible_move_pos.first.x > 0 && possible_move_pos.first.x < 8
                    && possible_move_pos.first.y > 0 && possible_move_pos.first.y < 8)
            {
                if(m_game->PositionHasPawn(possible_move_pos.first))
                    continue;
                int diff_x = m_current_target.first - possible_move_pos.first.x;
                int diff_y = m_current_target.second - possible_move_pos.first.y;
                possible_moves_count++;
                if(diff_x <= best_diff_x && diff_y <= best_diff_y)
                {
                    best_move = possible_move_pos;
                    best_diff_x = diff_x;
                    best_diff_y = diff_y;
                }
            }
        }
        if(possible_moves_count > 0)
        {
            m_game->MovePawn(m_current_pawn, best_move.second);
            data.player_turn = true;
        }
        else
        {
            m_pawns_to_move.push_back(m_current_pawn);
            m_pawns_to_move.pop_front();
            m_current_pawn = m_pawns_to_move.front();
        }
    }
}

void AiComponent::SetGame(Game& game) noexcept
{
    m_game = &game;
    for(int i =0; i < 3; i++)
        for(int j=0; j<3; j++)
        m_pawns_to_move.push_back(game.Data().black_pawns[i + (j*3)]);
}

void AiComponent::Update()
{
    MakeTurn();
}

std::string_view AiComponent::Name()
{
    return "ai"sv;
}

void AiComponent::ChoosePawn()
{
    PositionComponent* pos = ECSManager::Instance().GetComponent<PositionComponent>(m_current_pawn, "position");
    if(!pos)
        return;

    std::pair<int, int> const& current_pawn_position = pos->GetPosition();
    if(current_pawn_position == m_current_target)
    {
        m_current_pawn = m_pawns_to_move.front();
        m_pawns_to_move.pop_front();

        m_current_target = m_available_slots.front();
        m_available_slots.pop_front();
    }
}
} // namespace not_chess
