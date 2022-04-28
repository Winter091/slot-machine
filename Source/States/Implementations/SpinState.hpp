#ifndef _SPINSTATE_H_
#define _SPINSTATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

#include <chrono>

class SpinState final : public IState
{
public:
    SpinState(std::chrono::milliseconds maxDuration);

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine, float dt) override;

    virtual ~SpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_maxEndTime;
};

#endif