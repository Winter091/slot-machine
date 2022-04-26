#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <src/Buttons/Events/ButtonEvent.hpp>

class SlotMachine;

class IState
{
public:
    virtual void HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event) = 0;
    virtual void Update(SlotMachine* slotMachine) = 0;

    virtual ~IState() {};
};

#endif