#include <input_component.hpp>

namespace not_chess
{
using namespace std::literals;

InputComponent::InputComponent() : m_input_handler([this](core::Input::Key key)
                                {
                                    OnInput(key);
                                })
{

}

void InputComponent::OnInput(core::Input::Key key)
{
    // TODO:
}

std::string_view InputComponent::Name()
{
    return "input"sv;
}

}
