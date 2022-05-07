#ifndef _IDLE_STATE_H_
#define _IDLE_STATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

class IdleState final : public IState
{
public:
    IdleState() = default;

    virtual IState* HandleEvent(SlotMachine& slotMachine, const IEvent& input) override;
    virtual IState* Update(SlotMachine& slotMachine, float dt) override;
    virtual inline EStateName GetName() const override { return EStateName::Idle; }

    virtual ~IdleState() override {};
};

#endif