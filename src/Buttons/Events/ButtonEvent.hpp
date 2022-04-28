#ifndef _BUTTONEVENT_H_
#define _BUTTONEVENT_H_

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