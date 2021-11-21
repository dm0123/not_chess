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
    core::Event<core::Input::Key> const& InputHandler() const noexcept { return m_input_handler; }
private:
    core::Event<core::Input::Key> m_input_handler;
};
} // namespace not_chess
