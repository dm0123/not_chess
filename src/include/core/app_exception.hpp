#pragma once
#include <string>
#include <string_view>
#include <exception>

namespace not_chess::core
{
/// Main app exception
class AppException : public std::exception
{
public:
    AppException(std::string_view err) : m_exc(err)
    {
    }

    AppException(char const* err) : m_exc(err)
    {
    }

    const char* what() const noexcept override
    {
        return m_exc.data();
    }

private:
    std::string m_exc;
};
} // namespace not_chess::core
