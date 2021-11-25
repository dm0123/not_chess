#include <game.hpp>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
    try
    {
        not_chess::Game g;
        g.Init();
        g.Run();
        g.Shutdown();
    }
    catch(not_chess::core::AppException const& e)
    {
        std::cout << "Exception in main thread: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
