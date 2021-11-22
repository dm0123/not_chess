#include <ai_component.hpp>

namespace not_chess
{
using namespace std::literals;

void AiComponent::MakeTurn(std::vector<EntityId> pawns)
{
    // TODO:
}

std::string_view AiComponent::Name()
{
    return "ai"sv;
}
} // namespace not_chess
