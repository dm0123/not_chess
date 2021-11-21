#pragma once
#include <string>
#include <core/asset_manager.hpp>

namespace not_chess::core
{
class SoundAsset : public AbstractAsset
{
public:
};

class Sound
{
public:
    Sound() = default;
    ~Sound() = default;

    void RegisterSound(std::string name, AssetHandle sound);
    void Play(std::string sound_name);
private:
    std::unordered_map<std::string, AssetHandle> m_sounds;
};
} // namespace not_chess::core
