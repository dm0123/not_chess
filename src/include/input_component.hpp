#pragma once
#include <component.hpp>
#include <core/events.hpp>
#include <core/input.hpp>

namespace not_chess
{
class InputComponent : public AbstractComponent
{
public:
    InputComponent();
    void OnInput(core::Input::Key key);
    core::EventHandler<core::Input::Key> const& InputHandler() const noexcept { return m_input_handler; }
    std::string_view Name() const noexcept override;
private:
    core::EventHandler<core::Input::Key> m_input_handler;
};
} // namespace not_chess
