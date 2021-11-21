#include <game.hpp>

int main(int /*argc*/, char** /*argv*/)
{
    not_chess::Game g;
    g.Init();
    g.Run();
    g.Shutdown();
    return 0;
}
