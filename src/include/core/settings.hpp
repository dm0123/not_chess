#pragma once

#include <string>
#include <unordered_map>
#include <core/app_exception.hpp>

namespace not_chess::core
{
class SettingsException : public AppException
{
public:
    SettingsException(std::string_view err) : AppException(err)
    {
    }

    SettingsException(char const* err) : AppException(err)
    {
    }
};

class Settings
{
public:
    Settings() = default;
    ~Settings() = default;

    void SetSetting(std::string const& setting_name, int value ) noexcept;
    int GetSetting(std::string const& setting_name) const;
private:
    std::unordered_map<std::string, int> m_settings;
};
} // namespace not_chess::core
