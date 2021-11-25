#pragma once

#include <core/asset_manager.hpp>
#include <core/screen.hpp>
#include <entity.hpp>
#include <component.hpp>

#include <SFML/Graphics/Font.hpp>

namespace not_chess
{
using namespace std::literals;

class FontAsset : public core::AbstractAsset
{
public:
    FontAsset(std::string name, std::string path);
    sf::Font const& GetFont() const noexcept { return m_font; }

    void Load() override;
private:
    sf::Font m_font;
};

class TextComponent : public AbstractComponent
{
public:
    void AddAsset(std::string_view name) override;
    std::string_view Name() const noexcept override;

    void SetString(std::string_view str) { m_drawable.SetString(str); }
    void SetVisible(bool visible) noexcept { m_drawable.SetVisible(visible); }
private:
    core::AssetHandle m_text_asset;
    core::TextItem m_drawable;
};
} // namespace not_chess
