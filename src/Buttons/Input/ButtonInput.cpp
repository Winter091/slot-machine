#include "ButtonInput.hpp"

ButtonInput::ButtonInput(EButtonType type, EButtonAction action)
    : m_type(type), m_action(action)
{}

EButtonType ButtonInput::GetType()
{
    return m_type;
}

EButtonAction ButtonInput::GetAction()
{
    return m_action;
}