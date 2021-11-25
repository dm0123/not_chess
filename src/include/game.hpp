#pragma once

#include <core/app.hpp>
#include <core/events.hpp>
#include <core/input.hpp>
#include <core/screen.hpp>
#include <core/scores.hpp>
#include <core/sound.hpp>
#include <core/settings.hpp>

#include <entities_factory.hpp>
#include <screen_factory.hpp>
#include <entity.hpp>

#include <SFML/System/Clock.hpp>

#include <memory>
#include <vector>

namespace not_chess
{
/// Main class which holds all data and screens
class Game
{
public:
    friend class GameEntitiesFactory;
    friend class GameScreensFactory;

    enum class State : int
    {
        Finished, Playing, Paused
    };

    struct GameData
    {
        std::vector<EntityId> white_pawns;
        std::vector<EntityId> black_pawns;

        EntityId player; // TODO: unused
        EntityId ai_player;
        EntityId board;

        EntityId paused_text;
        EntityId your_turn_text;
        EntityId general_info_text;
        EntityId winner_text;

        bool player_turn { true };
        bool player_won { false };
    };


    Game();
    ~Game() = default;

    void Init();
    void Run();
    void Shutdown();
    void Reset();

    void AddStateChangeListener(core::EventHandler<State> state_changed);
    void AddTickEventListener(core::EventHandler<> tick_listener);
    void OnWindowEvent(sf::Event event);
    void OnDrawEvent();
    void OnInput(core::Input::Key key);

    void OnStateChange(State new_state);

    void OnPause();
    void OnPlay();
    void OnFinished();

    void AddScreen(std::unique_ptr<core::Screen>&& screen_ptr);
    GameData& Data() noexcept { return m_data; }
    State CurrentState() const noexcept { return m_state; }

    /**
     * @brief MovePawn move pawn to direction
     * @param pawn pawn id
     * @param key arrows or WASD controls
     * @return true if pawn was moved
     */
    bool MovePawn(EntityId pawn, core::Input::Key key);

    /**
     * @brief PositionHasPawn return if there is pawn on those coordinates
     * @param pos position to check
     * @param is_black true if pawn on this position is black. Do not check this if return value is false
     * @return true if position has pawn
     */
    bool PositionHasPawn(sf::Vector2i pos, bool& is_black);

private:
    void LoadAssets();
    void MakeEntities();
    void InitScreens();

    EntityId FindActivePawn();

    // hardcoded values
    void InitPawnPositions(std::vector<EntityId>& pawns, int offset);

    bool m_finished = false; // TODO: may be atomic_bool in multithreaded environment

    State m_state = State::Paused; // hardcode playing state for now

    core::App m_app;
    core::Input m_input;
    std::vector<std::unique_ptr<core::Screen>> m_screens;
    size_t m_current_screen_index = 0;

    GameScreensFactory m_screen_factory;
    GameEntitiesFactory m_entities_factory;

    core::EventHandler<> m_finished_handler;
    core::EventHandler<State> m_state_changed_handler; // This is handler for game logic state change
    core::EventHandler<> m_draw_event_handler;
    core::EventHandler<core::Input::Key> m_input_event_hander;

    core::Event<State> m_state_event; // This is event firing when state is changed from handler above
    core::Event<> m_tick_event;

    sf::Clock m_clock;
    GameData m_data;
};
} // namespace not_chess
