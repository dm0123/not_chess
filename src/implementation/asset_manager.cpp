#include <core/asset_manager.hpp>

namespace not_chess::core
{
AssetManager& AssetManager::Instance()
{
    static AssetManager instance;
    return instance;
}

const AbstractAsset& AssetManager::GetByName(std::string_view name) const
{
    auto it = m_assets_by_name.find( std::string{ name } );
    if(it == m_assets_by_name.end())
        throw AssetException("Invalid asset name");
    return GetByHandle(it->second);
}

const AbstractAsset& AssetManager::GetByHandle(AssetHandle handle) const
{
    if(handle >= m_assets.size())
        throw AssetException("Invalid asset handle");
    auto const& asset_ptr = m_assets.at(handle);
    return *asset_ptr.get();
}

AssetHandle AssetManager::GetHandleByName(std::string_view name) const
{
    auto it = m_assets_by_name.find(std::string{ name });
    if(it == m_assets_by_name.end())
        return INVALID_ASSET_HANDLE;
    return it->second;
}

void AssetManager::Load()
{
    for(auto& asset_ptr : m_assets)
        asset_ptr->Load();
}
} // namespace not_chess::core
