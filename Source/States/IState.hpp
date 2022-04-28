#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <Source/Buttons/Events/ButtonEvent.hpp>

class SlotMachine;

class IState
{
public:
    IState() = default;
    IState(const IState&) = delete;
    IState& operator=(const IState&) = delete;

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event) = 0;
    virtual IState* Update(SlotMachine* slotMachine, float dt) = 0;

    virtual ~IState() {};
};

#endif