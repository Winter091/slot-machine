#ifndef _ISTATE_H_
#define _ISTATE_H_

#include <Source/Events/IEvent.hpp>
#include <Source/States/EStateName.hpp>

class SlotMachine;

class IState
{
public:
    IState() = default;
    IState(const IState&) = delete;
    IState& operator=(const IState&) = delete;

    virtual IState* HandleEvent(SlotMachine& slotMachine, const IEvent& event) = 0;
    virtual IState* Update(SlotMachine& slotMachine, float dt) = 0;
    virtual EStateName GetName() const = 0;

    virtual ~IState() {};
};

#endif