#ifndef _IDLE_STATE_H_
#define _IDLE_STATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

class IdleState final : public IState
{
public:
    IdleState() = default;

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine, float dt) override;

    virtual ~IdleState() override {};
};

#endif