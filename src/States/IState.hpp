#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <src/Buttons/Events/ButtonEvent.hpp>

class SlotMachine;

class IState
{
public:
    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event) = 0;
    virtual IState* Update(SlotMachine* slotMachine, float dt) = 0;

    virtual const char* GetDebugName() const = 0;

    virtual ~IState() {};
};

#endif