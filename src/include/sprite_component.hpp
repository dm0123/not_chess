#pragma once

#include <component.hpp>
#include <core/asset_manager.hpp>
#include <core/screen.hpp>

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

#include <string>
#include <string_view>

namespace not_chess
{
using namespace std::literals;

class TextureAsset : public core::AbstractAsset
{
public:
    TextureAsset(std::string name, std::string path);
    sf::Texture const& Texture() const noexcept { return m_texture; }
    void Load() override;
private:
    sf::Texture m_texture;
};

class SpriteComponent : public AbstractComponent
{
public:
    void Init() override;
    void AddAsset(std::string_view name) override;
    std::string_view Name() override { return "sprite"sv; }
private:
    core::AssetHandle m_asset;
    core::SimpleSpriteItem m_drawable;
};
} // namespace not_chess
