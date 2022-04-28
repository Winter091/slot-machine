#ifndef _BUTTON_EVENT_H_
#define _BUTTON_EVENT_H_

#include "EButtonType.hpp"
#include "EButtonAction.hpp"

class ButtonEvent
{
public:
    ButtonEvent() = default;
    ButtonEvent(EButtonType type, EButtonAction action);

    EButtonType GetType() const;
    EButtonAction GetAction() const;

private:
    EButtonType m_type;
    EButtonAction m_action;
};

#endif