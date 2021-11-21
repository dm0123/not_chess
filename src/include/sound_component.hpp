#pragma once
#include <component.hpp>

namespace not_chess
{
class SoundComponent : public AbstractComponent
{
public:
    void Init() override;
    void AddAsset(std::string_view asset_name) override;
};
} // namespace not_chess
