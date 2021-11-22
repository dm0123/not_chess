#include <game.hpp>
#include <core/asset_manager.hpp>
#include <sprite_component.hpp>
#include <position_component.hpp>

using namespace std::literals;

namespace not_chess
{
namespace
{
    // lock at 60 frames per second
    const auto TIME_PER_FRAME = sf::seconds( 1.0f / 60.0f );

    enum  Screens : size_t
    {
        sGame,
        sMainMenu,
        sPause,
        sSettings,
        sScores
    };
}

Game::Game() : m_screen_factory(*this),
               m_entities_factory(*this), m_finished_handler([this]()
            {
                m_finished = true;
            }),
               m_state_changed_handler([this](State new_state)
            {
                m_state = new_state;
            }),
            m_draw_event_handler([this](){
                OnDrawEvent();
            })
{
}

void Game::Init()
{
    m_app.Init();
    m_app.AddFinishedEventHandler(m_finished_handler);
    m_app.AddWindowEventHandler(m_input.GetWindowEventHandler());
    m_app.AddDrawEventHandler(m_draw_event_handler);

    LoadAssets();
    MakeEntities();
    InitScreens();
    ECSManager::Instance().Init();
}

void Game::Run()
{
    sf::Time time_since_last_update = sf::Time::Zero;
    for(;;)
    {
        m_app.Run();
        time_since_last_update += m_clock.restart();
        while(time_since_last_update > TIME_PER_FRAME)
        {
            time_since_last_update -= TIME_PER_FRAME;
            if(m_state == State::Playing)
                m_tick_event();
        }
        if(m_finished)
            break;
    }
}

void Game::Shutdown()
{
    m_app.Shutdown();
}

void Game::AddStateChangeListener(core::EventHandler<State> state_changed)
{
    m_state_event += state_changed;
}

void Game::AddTickEventListener(core::EventHandler<> tick_listener)
{
    m_tick_event += tick_listener;
}


void Game::OnDrawEvent()
{
    if(m_screens.size() > 0)
        m_screens[m_current_screen_index].Draw(m_app.Window());
}

void Game::OnStateChange(State new_state)
{
    m_state = new_state;
    switch(m_state)
    {
    case State::Paused:
        m_current_screen_index = Screens::sPause;
        OnPause();
        break;
    case State::Playing:
        m_current_screen_index = Screens::sGame;
        OnPlay();
        break;
    case State::MainMenu:
        OnMainMenu();
        m_current_screen_index = Screens::sMainMenu;
        break;
    }
}

void Game::OnPause()
{
}

void Game::OnPlay()
{
}

void Game::OnMainMenu()
{
}

void Game::LoadAssets()
{
    // TODO: this should be loaded from file, but we hardcode assets for now
    auto& assets = core::AssetManager::Instance();

    // pawn assets
    assets.MakeAsset<TextureAsset>("black_pawn"sv, "assets/sprites/blackPawn.png"sv);
    assets.MakeAsset<TextureAsset>("white_pawn"sv, "assets/sprites/whitePawn.png"sv);

    assets.Load();
}

void Game::MakeEntities()
{
    m_entities_factory.MakePawns();
    m_entities_factory.MakeBoard();

    // hardcode pawn initial positions
    InitPawnPositions(m_data.black_pawns, 0);
    InitPawnPositions(m_data.white_pawns, 5);
}

void Game::InitScreens()
{
    m_screens.push_back(m_screen_factory.MakeGameScreen());
    m_screens.push_back(m_screen_factory.MakePauseScreen());
    m_screens.push_back(m_screen_factory.MakeMainMenuScreen());
}

void Game::InitPawnPositions(std::vector<EntityId>& pawns, int offset)
{
    for(int i = 0; i < 3; ++i)
    {
        int column = i + offset;
        for(int j = 0; j < 3; ++j)
        {
            int row = j + offset;
            EntityId pawn_id = pawns[j + (i *3)];
            auto& pos_ptr = ECSManager::Instance().ComponentByName(pawn_id, "position"sv);
            if(pos_ptr)
            {
                PositionComponent* position = static_cast<PositionComponent*>(pos_ptr.get());
                position->SetPosition(row, column);
            }
        }
    }
}
} // namespace not_chess
