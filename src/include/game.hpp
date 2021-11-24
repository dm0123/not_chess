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
#include <SFML/System/Clock.hpp>
#include <entity.hpp>

#include <memory>
#include <vector>
#include <optional>

namespace not_chess
{
class Game
{
public:
    friend class GameEntitiesFactory;
    friend class GameScreensFactory;

    enum class State : int
    {
        MainMenu, Playing, Paused
    };

    enum class InputMode
    {
        Choosing,
        Moving
    };

    struct PlayerInputMode
    {
        InputMode mode = InputMode::Choosing;
        void Next() noexcept
        {
            if(mode == InputMode::Choosing)
                mode = InputMode::Moving;
            else mode = InputMode::Choosing;
        }
    };


    struct GameData
    {
        std::vector<EntityId> white_pawns;
        std::vector<EntityId> black_pawns;

        EntityId player;
        EntityId ai_player;
        EntityId board;

        bool player_turn { true };
        std::optional<sf::Vector2i> active_tile;
        sf::Vector2i cursor_tile {0, 0};
        PlayerInputMode input_mode;
    };


    Game();
    ~Game() = default;

    void Init();
    void Run();
    void Shutdown();

    void AddStateChangeListener(core::EventHandler<State> state_changed);
    void AddTickEventListener(core::EventHandler<> tick_listener);
    void OnWindowEvent(sf::Event event);
    void OnDrawEvent();
    void OnInput(core::Input::Key key);

    void OnStateChange(State new_state);

    void OnPause();
    void OnPlay();
    void OnMainMenu();

    void AddScreen(std::unique_ptr<core::Screen>&& screen_ptr);
    GameData& Data() { return m_data; }

    bool MovePawn(EntityId pawn, core::Input::Key key);
    bool PositionHasPawn(sf::Vector2i pos);

private:
    void LoadAssets();
    void MakeEntities();
    void InitScreens();

    void MoveCursor(core::Input::Key key);
    void PlayerMovePawn(core::Input::Key key);

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
