#include <game.hpp>
#include <core/asset_manager.hpp>
#include <sprite_component.hpp>
#include <position_component.hpp>
#include <grid_component.hpp>
#include <text_component.hpp>

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
        sPause,
        sFinished,
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
            }),
            m_input_event_hander([this](core::Input::Key key){
                OnInput(key);
            })
{
}

void Game::Init()
{
    m_app.Init();
    m_app.AddFinishedEventHandler(m_finished_handler);
    m_app.AddWindowEventHandler(m_input.GetWindowEventHandler());
    m_app.AddDrawEventHandler(m_draw_event_handler);
    m_tick_event += ECSManager::Instance().TickListener();
    m_input.AddPressedEventHandler(m_input_event_hander);

    LoadAssets();
    MakeEntities();
    InitScreens();
    ECSManager::Instance().Init();
    OnStateChange(State::Playing);
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
            m_screens[m_current_screen_index]->Update();
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

void Game::Reset()
{
    m_data.white_pawns.clear();
    m_data.black_pawns.clear();
    m_data.player_turn = !m_data.player_turn;
    // hardcode pawn initial positions
    InitPawnPositions(m_data.black_pawns, 0);
    InitPawnPositions(m_data.white_pawns, 5);

    OnStateChange(State::Playing);
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
    if(m_screens.size() > 0 && m_screens[m_current_screen_index])
        m_screens[m_current_screen_index]->Draw(m_app.Window());
}

void Game::OnInput(core::Input::Key key)
{
    m_screens[m_current_screen_index]->OnInput(key);
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
    case State::Finished:
        OnFinished();
        m_current_screen_index = Screens::sFinished;
        break;
    }
}

void Game::OnPause()
{
    m_current_screen_index = Screens::sPause;
}

void Game::OnPlay()
{
    m_current_screen_index = Screens::sGame;
}

void Game::OnFinished()
{
    m_current_screen_index = Screens::sFinished;
}

void Game::AddScreen(std::unique_ptr<core::Screen>&& screen_ptr)
{
    m_screens.push_back(std::move(screen_ptr));
}

void Game::LoadAssets()
{
    // TODO: this should be loaded from file, but we hardcode assets for now
    auto& assets = core::AssetManager::Instance();

    // pawn assets
    assets.MakeAsset<TextureAsset>("black_pawn"sv, "assets/sprites/blackPawn.png"sv);
    assets.MakeAsset<TextureAsset>("white_pawn"sv, "assets/sprites/whitePawn.png"sv);
    assets.MakeAsset<FontAsset>("font", "assets/fonts/SIXTY.TTF");

    assets.Load();
}

void Game::MakeEntities()
{
    m_entities_factory.MakePawns();
    m_entities_factory.MakeBoard();
    m_entities_factory.MakeAI();
    m_entities_factory.MakePlayer();
    m_entities_factory.MakeText();

    // hardcode pawn initial positions
    InitPawnPositions(m_data.black_pawns, 0);
    InitPawnPositions(m_data.white_pawns, 5);
}

void Game::InitScreens()
{
    m_screen_factory.Init();
}

bool Game::MovePawn(EntityId pawn_id, core::Input::Key key)
{
    PositionComponent* pos = ECSManager::Instance().GetComponent<PositionComponent>(pawn_id, "position");
    if(!pos)
        return false;
    sf::Vector2i new_position { pos->GetPosition().first, pos->GetPosition().second };


    switch(key)
    {
    case core::Input::Key::Left:
    case core::Input::Key::A:
        new_position.x--;
        if(new_position.x < 0)
            new_position.x = 0;
        break;
    case core::Input::Key::Right:
    case core::Input::Key::D:
        new_position.x++;
        if(new_position.x > 7)
            new_position.x = 7;
        break;
    case core::Input::Key::Up:
    case core::Input::Key::W:
       new_position.y--;
        if(new_position.y < 0)
            new_position.y = 0;
        break;
    case core::Input::Key::Down:
    case core::Input::Key::S:
        new_position.y++;
        if(new_position.y > 7)
            new_position.y = 7;
    default:
        break;
    }

    // if no pawn here then move here
    bool is_black;
    if(!PositionHasPawn(new_position, is_black))
    {
        pos->SetPosition(new_position.x, new_position.y);
        return true;
    }
    return false;
}

bool Game::PositionHasPawn(sf::Vector2i position, bool& is_black)
{
    // Find if new position has pawn in it
    auto pred = [&position](EntityId pawn_id)
    {
        PositionComponent* pos = ECSManager::Instance().GetComponent<PositionComponent>(pawn_id, "position");
        if(pos)
            return pos->GetPosition().first == position.x && pos->GetPosition().second == position.y;
        return false;
    };
    auto white_it = std::find_if(m_data.white_pawns.begin(), m_data.white_pawns.end(), pred);
    if(white_it != m_data.white_pawns.end())
    {
        is_black = false;
        return true;
    }
    auto black_it = std::find_if(m_data.black_pawns.begin(), m_data.black_pawns.end(), pred);
    if(black_it != m_data.black_pawns.end())
    {
        is_black = true;
        return true;
    }
    return false;
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
            PositionComponent* position = ECSManager::Instance().GetComponent<PositionComponent>(pawn_id, "position"sv);
            if(position)
                position->SetPosition(row, column);
        }
    }
}
} // namespace not_chess
