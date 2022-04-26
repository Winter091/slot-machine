#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <src/Buttons/Input/ButtonInput.hpp>

class SlotMachine;

class IState
{
public:
    virtual void HandleButtonInput(SlotMachine* slotMachine, const ButtonInput& input) = 0;
    virtual void Update(SlotMachine* slotMachine) = 0;

    virtual ~IState() {};
};

#endif