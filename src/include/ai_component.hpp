#pragma once
#include <component.hpp>
#include <deque>

namespace not_chess
{
class Game;

// Simple ai moving one pawn at a time
class AiComponent : public AbstractComponent
{
public:
    AiComponent();
    void MakeTurn();
    void SetGame(Game& game) noexcept;
    void Update() override;
    std::string_view Name() const noexcept override;
private:
    void ChoosePawn();

    std::deque<std::pair<int, int>> m_available_slots;
    std::deque<EntityId> m_pawns_to_move;

    EntityId m_current_pawn;
    std::pair<int, int> m_current_target;
    Game* m_game = nullptr;
};
}
