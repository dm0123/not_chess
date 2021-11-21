#include <core/settings.hpp>
#include <core/app_exception.hpp>

namespace not_chess::core
{
void Settings::SetSetting(const std::string& setting_name, int value) noexcept
{
    m_settings[setting_name] = value;
}

int Settings::GetSetting(const std::string& setting_name) const
{
    auto it = m_settings.find(setting_name);
    if(it == m_settings.end())
        throw SettingsException("Failed to find setting");

    return it->second;
}
} // namespace not_chess::core
