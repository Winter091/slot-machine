#ifndef _IDLESTATE_H_
#define _IDLESTATE_H_

#include <src/States/IState.hpp>
#include <src/Slots/SlotMachine.hpp>

class IdleState final : public IState
{
public:
    IdleState() = default;

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine, float dt) override;

    virtual ~IdleState() override {};
};

#endif