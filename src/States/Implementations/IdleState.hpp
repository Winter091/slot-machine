#ifndef _IDLESTATE_H_
#define _IDLESTATE_H_

#include <src/States/IState.hpp>
#include <src/Slots/SlotMachine.hpp>

class IdleState : public IState
{
public:
    virtual void HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual void Update(SlotMachine* slotMachine) override;

    virtual ~IdleState() override;
};

#endif