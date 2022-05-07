#include "ButtonInput.hpp"

ButtonInput& ButtonInput::GetInstance()
{
    static ButtonInput input;
    return input;
}

void ButtonInput::HandleWindowEvents(IWindow* window)
{
    auto& instance = GetInstance();

    for (EButtonType buttonType : { EButtonType::Start, EButtonType::Stop, EButtonType::WinMessage }) {
        if (window->IsButtonPressed(buttonType)) {
            instance.m_buttonEvents.push(ButtonEvent(buttonType, EButtonAction::Press));
        }
    }
}

bool ButtonInput::GetNextEvent(ButtonEvent& outEvent)
{
    auto& instance = GetInstance();
    
    if (instance.m_buttonEvents.empty()) {
        return false;
    }

    outEvent = instance.m_buttonEvents.front();
    instance.m_buttonEvents.pop();
    return true;
}

