#include "ButtonEvent.hpp"

ButtonEvent::ButtonEvent(EButtonType type, EButtonAction action)
    : m_type(type), m_action(action)
{}

EButtonType ButtonEvent::GetType() const
{
    return m_type;
}

EButtonAction ButtonEvent::GetAction() const
{
    return m_action;
}