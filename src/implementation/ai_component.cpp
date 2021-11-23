#include <ai_component.hpp>
#include <position_component.hpp>
#include <game.hpp>

namespace not_chess
{
using namespace std::literals;


void AiComponent::MakeTurn()
{
    if(!m_game)
        return;
    Game::GameData& data = m_game->Data();
    if(data.player_turn)
        return;

    // Find lower right element
    auto it = std::max_element(data.black_pawns.begin(), data.black_pawns.end(), [](EntityId const& left_id, EntityId const& right_id){
            PositionComponent* left = ECSManager::Instance().GetComponent<PositionComponent>(left_id, "position");
            PositionComponent* right = ECSManager::Instance().GetComponent<PositionComponent>(right_id, "position");
            if(left && right)
            {
                return left->GetPosition().first >= right->GetPosition().first ||
                       left->GetPosition().second >= right->GetPosition().second;
            }

            return false;
    });
    if(it == data.black_pawns.end())
        it = data.black_pawns.begin();

    PositionComponent* pawn_pos = ECSManager::Instance().GetComponent<PositionComponent>(*it, "position");
    if(pawn_pos)
    {
        auto position = pawn_pos->GetPosition();
        for(auto& possible_move_pos : { std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first -1 , position.second), core::Input::Key::Left},
                                        std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first + 1, position.second), core::Input::Key::Right},
                                        std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first , position.second -1 ), core::Input::Key::Up},
                                        std::pair<sf::Vector2i, core::Input::Key>{sf::Vector2i(position.first , position.second + 1 ), core::Input::Key::Right}})
        {
            if(possible_move_pos.first.x > 0 && possible_move_pos.first.x < 8 && possible_move_pos.first.y > 0 && possible_move_pos.first.y < 8)
                if(m_game->MovePawn(*it, possible_move_pos.second))
                    break;
        }
    }

    data.player_turn = true;
}

void AiComponent::Update()
{
    MakeTurn();
}

std::string_view AiComponent::Name()
{
    return "ai"sv;
}
} // namespace not_chess
