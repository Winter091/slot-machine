#include "ButtonEvent.hpp"

ButtonEvent::ButtonEvent(EButtonType type, EButtonAction action)
    : m_type(type), m_action(action)
{}

EButtonType ButtonEvent::GetType()
{
    return m_type;
}

EButtonAction ButtonEvent::GetAction()
{
    return m_action;
}