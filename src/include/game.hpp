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


    struct GameData
    {
        std::vector<EntityId> white_pawns;
        std::vector<EntityId> black_pawns;
        EntityId player;
        EntityId ai_player;
        EntityId board;
        bool player_turn = true;
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

    void OnStateChange(State new_state);

    void OnPause();
    void OnPlay();
    void OnMainMenu();

private:
    void LoadAssets();
    void MakeEntities();
    void InitScreens();

    // hardcoded values
    void InitBlackPawnPositions();
    void InitWhitePawnPositions();

    bool m_finished = false; // TODO: may be atomic_bool in multithreaded environment

    State m_state;

    core::App m_app;
    core::Input m_input;
    std::vector<core::Screen> m_screens;
    size_t m_current_screen_index = 0;

    GameScreensFactory m_screen_factory;
    GameEntitiesFactory m_entities_factory;

    core::EventHandler<> m_finished_handler;
    core::EventHandler<State> m_state_changed_handler; // This is handler for game logic state change
    core::EventHandler<> m_draw_event_handler;

    core::Event<State> m_state_event; // This is event firing when state is changed from handler above
    core::Event<> m_tick_event;

    sf::Clock m_clock;
    GameData m_data;
};
} // namespace not_chess
