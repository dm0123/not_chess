#include <entities_factory.hpp>
#include <entity.hpp>
#include <sprite_component.hpp>
#include <grid_component.hpp>
#include <position_component.hpp>
#include <input_component.hpp>
#include <ai_component.hpp>
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
} // namespace not_chess
