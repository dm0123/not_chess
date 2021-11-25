#include <text_component.hpp>

namespace not_chess
{
FontAsset::FontAsset(std::string name, std::string path) : core::AbstractAsset(std::move(name), std::move(path))
{
}

void FontAsset::Load()
{
    m_font.loadFromFile(m_path);
}

void TextComponent::AddAsset(std::string_view name)
{
    auto& asset_manager = core::AssetManager::Instance();
    m_text_asset = asset_manager.GetHandleByName(name);
    FontAsset const& font = static_cast<FontAsset const&>(asset_manager.GetByHandle(m_text_asset));
    sf::Text text;
    text.setFont(font.GetFont());
    m_drawable.SetText(text);
    m_drawables.push_back(&m_drawable);
}

std::string_view TextComponent::Name() const noexcept
{
    return"text"sv;
}

} // namespace not_chess
