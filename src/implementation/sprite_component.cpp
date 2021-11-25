#include <sprite_component.hpp>

namespace not_chess
{
TextureAsset::TextureAsset(std::string name, std::string path)
    : core::AbstractAsset(std::move(name), std::move(path))
{
}

void TextureAsset::Load()
{
    m_texture.loadFromFile(m_path);
}

void SpriteComponent::AddAsset(std::string_view name)
{
    m_asset = core::AssetManager::Instance().GetHandleByName(name);
    TextureAsset const& texture = static_cast<TextureAsset const&>(core::AssetManager::Instance().GetByHandle(m_asset));
    sf::Sprite sprite;
    sprite.setTexture(texture.Texture());
    m_drawable.SetSprite(sprite);
    m_drawables.push_back(&m_drawable);
}

} // namespace not_chess
