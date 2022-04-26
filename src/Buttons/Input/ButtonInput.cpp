#include "ButtonInput.hpp"

#include <iostream>

ButtonInput::ButtonInput()
{}

ButtonInput* ButtonInput::GetInstance()
{
    static ButtonInput input;
    return &input;
}

void ButtonInput::HandleWindowEvents(IWindow* window)
{
    auto instance = GetInstance();
    
    if (window->IsStartButtonPressed()) {
        instance->m_buttonEvents.push(ButtonEvent(EButtonType::Start, EButtonAction::Press));
    }
    if (window->IsStopButtonPressed()) {
        instance->m_buttonEvents.push(ButtonEvent(EButtonType::Stop, EButtonAction::Press));
    }
}

bool ButtonInput::GetNextEvent(ButtonEvent& outEvent)
{
    auto instance = GetInstance();
    
    if (instance->m_buttonEvents.empty()) {
        return false;
    }

    outEvent = instance->m_buttonEvents.front();
    instance->m_buttonEvents.pop();
    return true;
}

