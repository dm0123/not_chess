#pragma once
#include <component.hpp>

namespace not_chess
{
class Game;

class AiComponent : public AbstractComponent
{
public:
    void MakeTurn();
    void SetGame(Game& game) noexcept { m_game = &game; }
    void Update() override;
    std::string_view Name() override;
private:
    Game* m_game = nullptr;
};
}
