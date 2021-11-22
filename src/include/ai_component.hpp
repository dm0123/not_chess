#pragma once
#include <component.hpp>

namespace not_chess
{
class AiComponent : public AbstractComponent
{
public:
    void MakeTurn(std::vector<EntityId> pawns);
    std::string_view Name() override;
};
}
