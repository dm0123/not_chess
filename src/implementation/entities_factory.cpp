#include <entities_factory.hpp>
#include <entity.hpp>
#include <sprite_component.hpp>
#include <grid_component.hpp>
#include <position_component.hpp>
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

    // hardcode positions
    for(EntityId entity_id : black_pawns)
    {
        Entity const& entity = ECSManager::Instance().Get(entity_id);

    }

    std::vector<EntityId> white_pawns;
    white_pawns.reserve(9);
    for(int i = 0; i < pawns_count; ++i)
    {
        MakePawn(false, i);
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
} // namespace not_chess
