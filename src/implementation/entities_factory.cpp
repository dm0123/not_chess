#include <entities_factory.hpp>
#include <entity.hpp>
#include <sprite_component.hpp>
#include <grid_component.hpp>
#include <position_component.hpp>
#include <input_component.hpp>
#include <ai_component.hpp>
#include <text_component.hpp>
#include <game.hpp>

#include <vector>
#include <memory>
#include <string_view>
#include <string>

using namespace std::literals;

namespace not_chess
{
namespace
{
EntityId MakePawn(bool is_black, int id)
{
    auto& ecs_instance = ECSManager::Instance();
    std::vector<std::unique_ptr<AbstractComponent>> pawn_components;
    std::unique_ptr<SpriteComponent> sprite_c = std::make_unique<SpriteComponent>();
    if(is_black)
        sprite_c->AddAsset("black_pawn");
    else
        sprite_c->AddAsset("white_pawn");
    pawn_components.push_back(std::move(sprite_c));

    std::unique_ptr<PositionComponent> position_c = std::make_unique<PositionComponent>();
    pawn_components.push_back(std::move(position_c));

    EntityId pawn;
    if( is_black )
        pawn = ecs_instance.MakeEntity("black_pawn_" + std::to_string(id), std::move(pawn_components));
    else
        pawn = ecs_instance.MakeEntity("white_pawn_" + std::to_string(id), std::move(pawn_components));
    return pawn;
}
}

void GameEntitiesFactory::MakePawns() const
{
    constexpr auto pawns_count = 9; // we know how much pawns there are
    std::vector<EntityId> black_pawns;
    black_pawns.reserve(9);
    for(int i = 0; i < pawns_count; ++i)
    {
        black_pawns.push_back(MakePawn(true, i));
    }
    m_game.m_data.black_pawns = black_pawns;

    std::vector<EntityId> white_pawns;
    white_pawns.reserve(9);
    for(int i = 0; i < pawns_count; ++i)
    {
        white_pawns.push_back(MakePawn(false, i));
    }
    m_game.m_data.white_pawns = white_pawns;
}

void GameEntitiesFactory::MakeBoard() const
{
    auto& ecs_instance = ECSManager::Instance();
    std::vector<std::unique_ptr<AbstractComponent>> comps;
    auto grid_component = std::make_unique<GridComponent>();
    comps.push_back(std::move(grid_component));
    m_game.m_data.board = ecs_instance.MakeEntity("board", std::move(comps));
}

void GameEntitiesFactory::MakePlayer() const
{
    auto& ecs_instance = ECSManager::Instance();
    std::vector<std::unique_ptr<AbstractComponent>> comps;
    std::unique_ptr<InputComponent> input_component = std::make_unique<InputComponent>();
    comps.push_back(std::move(input_component));
    m_game.m_data.player = ecs_instance.MakeEntity("player", std::move(comps));
}

void GameEntitiesFactory::MakeAI() const
{
    auto& ecs_instance = ECSManager::Instance();
    std::vector<std::unique_ptr<AbstractComponent>> components;
    auto ai_component = std::make_unique<AiComponent>();
    ai_component->SetGame(m_game);
    components.push_back(std::move(ai_component));
    m_game.m_data.ai_player = ecs_instance.MakeEntity("ai_player", std::move(components));

}

void GameEntitiesFactory::MakeText() const
{
    auto& ecs_instance = ECSManager::Instance();
    auto window_size = m_game.m_app.Window().getSize();

    // Paused text
    auto pause_text_component = std::make_unique<TextComponent>();
    pause_text_component->AddAsset("font");
    pause_text_component->SetString("Paused");
    EntityId pause_text_id = ecs_instance.MakeEntity("pause_text", {});
    Entity& pause_text = ecs_instance.Get(pause_text_id);
    pause_text.AddComponent(std::move(pause_text_component));
    pause_text.SetPosition( sf::Vector2i(window_size / 2u) );
    m_game.m_data.paused_text = pause_text_id;


    // your turn text
    auto your_turn_text_component = std::make_unique<TextComponent>();
    your_turn_text_component->AddAsset("font");
    your_turn_text_component->SetString("Your turn");
    your_turn_text_component->SetVisible(false);
    EntityId your_turn_text_id = ecs_instance.MakeEntity("your_turn_text", {});

    Entity& your_turn_text = ecs_instance.Get(your_turn_text_id);
    your_turn_text.AddComponent(std::move(your_turn_text_component));
    your_turn_text.SetPosition(sf::Vector2i(0, 8*64.f - 5)); // dirty computation of 'below board on a left'
    m_game.m_data.your_turn_text = your_turn_text_id;

    // General info text
    auto general_info_text_component = std::make_unique<TextComponent>();
    general_info_text_component->AddAsset("font");
    general_info_text_component->SetString("Move cursor with arrows or WASD.\nChoose with SPACE and arrows or WASD.");
    EntityId general_info_text_id = ecs_instance.MakeEntity("general_info_text", {});

    Entity& general_info_text = ecs_instance.Get(general_info_text_id);
    general_info_text.AddComponent(std::move(general_info_text_component));
    general_info_text.SetPosition(sf::Vector2i(0, 8*64.f + 20)); // dirty computation of 'below board on a left'
    m_game.m_data.general_info_text = general_info_text_id;

    // Winner text
    auto winner_text_component = std::make_unique<TextComponent>();
    winner_text_component->AddAsset("font");
    winner_text_component->SetString("Winner is:");
    EntityId winner_text_id = ecs_instance.MakeEntity("winner_text", {});

    Entity& winner_text = ecs_instance.Get(winner_text_id);
    winner_text.AddComponent(std::move(winner_text_component));
    winner_text.SetPosition(sf::Vector2i( window_size / 2u )); // dirty computation of 'below board on a left'
    m_game.m_data.winner_text = winner_text_id;
}
} // namespace not_chess
