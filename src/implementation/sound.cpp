#include <core/sound.hpp>
#include <core/asset_manager.hpp>
#include <SFML/Audio/Sound.hpp>

namespace not_chess::core
{
void Sound::RegisterSound(std::string name, AssetHandle sound)
{
    m_sounds[name] = sound;
}

void Sound::Play(std::string sound_name)
{
    auto it = m_sounds.find(sound_name);
    if(it == m_sounds.end())
        return; // cannot find sound by that name
//    AssetManager::Instance().GetByHandle(it->second);
}
} // namespace not_chess
