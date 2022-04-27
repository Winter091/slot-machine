#ifndef _IDLESTATE_H_
#define _IDLESTATE_H_

#include <src/States/IState.hpp>
#include <src/Slots/SlotMachine.hpp>

class IdleState : public IState
{
public:
    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine, float dt) override;

    virtual const char* GetDebugName() const override { return "Idle"; }

    virtual ~IdleState() override {};
};

#endif