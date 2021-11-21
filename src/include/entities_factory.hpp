#pragma once

namespace not_chess
{
class Game;

class GameEntitiesFactory
{
public:
    GameEntitiesFactory(Game& g) : m_game(g)
    {
    }

    void MakePawns() const;
    void MakeBoard() const;
private:
    Game& m_game;
};
} // namespace not_chess
