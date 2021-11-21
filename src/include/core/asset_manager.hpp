#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <memory>
#include <core/app_exception.hpp>

namespace not_chess::core
{
using AssetHandle = uint32_t;
constexpr AssetHandle INVALID_ASSET_HANDLE = -1;

class AssetException : public AppException
{
public:
    AssetException(std::string_view err) : AppException(err)
    {
    }

    AssetException(char const* err) : AppException(err)
    {
    }
};

class AbstractAsset
{
public:
    // TODO: transform relative path to absolute or load from memory blob
    AbstractAsset(std::string name, std::string path) : m_name(std::move(name)), m_path(std::move(path))
    {
    }

    virtual ~AbstractAsset() = default;

    /// AssetManager will call this method to load an asset
    virtual void Load() {}

    std::string_view Name() const noexcept { return m_name; }
    std::string_view Path() const noexcept { return m_path; }
protected:
    std::string m_name;
    std::string m_path;
};

/**
 * @brief AssetManager is a class where assets are registered and loaded
 */
class AssetManager
{
public:
    static AssetManager& Instance();

    /// Factory method for asset initialization
    template<typename FinalAssetT>
    AssetHandle MakeAsset(std::string_view name, std::string_view path)
    {
        // TODO: make access to m_assets thread-safe
        auto asset = std::make_unique<FinalAssetT>(std::string{ name }, std::string{ path });
        AssetHandle index = static_cast<AssetHandle>(m_assets.size());
        m_assets.push_back(std::move(asset));
        m_assets_by_name[std::string{name}] = index;
        return index;
    }

    /// Call this to load all registered assets
    void Load();

    /// Find asset by name
    AbstractAsset const& GetByName(std::string_view name) const;

    /// Find asset by id
    AbstractAsset const& GetByHandle(AssetHandle handle) const;

    /// Find asset handle by its name
    AssetHandle GetHandleByName(std::string_view name) const;
private:
    AssetManager() = default;

    /// Vector of assets. AssetHandle is index in this vector
    std::vector<std::unique_ptr<AbstractAsset>> m_assets;
    /// Mapping for names of assets to its handles
    std::unordered_map<std::string, AssetHandle> m_assets_by_name;
};
} // namespace not_chess::core
