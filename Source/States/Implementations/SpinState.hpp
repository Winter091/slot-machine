#ifndef _SPIN_STATE_H_
#define _SPIN_STATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

#include <chrono>

class SpinState final : public IState
{
public:
    SpinState(std::chrono::milliseconds maxDuration);

    virtual IState* HandleButtonEvent(SlotMachine& slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine& slotMachine, float dt) override;
    virtual inline EStateName GetName() const override { return EStateName::Spin; }

    virtual ~SpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_maxEndTime;
};

#endif