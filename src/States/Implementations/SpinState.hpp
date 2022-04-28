#ifndef _SPINSTATE_H_
#define _SPINSTATE_H_

#include <src/States/IState.hpp>
#include <src/Slots/SlotMachine.hpp>

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