#ifndef _BUTTONEVENT_H_
#define _BUTTONEVENT_H_

#include "EButtonType.hpp"
#include "EButtonAction.hpp"

class ButtonEvent
{
public:
    ButtonEvent(EButtonType type, EButtonAction action);

    EButtonType GetType();
    EButtonAction GetAction();

private:
    EButtonType m_type;
    EButtonAction m_action;
};

#endif