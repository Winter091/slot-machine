#ifndef _BUTTONINPUT_H_
#define _BUTTONINPUT_H_

#include "EButtonType.hpp"
#include "EButtonAction.hpp"

class ButtonInput
{
public:
    ButtonInput(EButtonType type, EButtonAction action);

    EButtonType GetType();
    EButtonAction GetAction();

private:
    EButtonType m_type;
    EButtonAction m_action;
};

#endif