#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <src/Slots/SlotMachine.hpp>
#include <src/Buttons/Input/ButtonInput.hpp>

class IState
{
public:
    virtual void HandleButtonInput(SlotMachine& slotMachine, const ButtonInput& input) = 0;
    virtual void Update(SlotMachine& slotMachine) = 0;

    virtual ~IState() {};
};

#endif