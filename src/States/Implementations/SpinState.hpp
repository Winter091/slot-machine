#ifndef _SPINSTATE_H_
#define _SPINSTATE_H_

#include <src/States/IState.hpp>
#include <src/Slots/SlotMachine.hpp>

#include <chrono>

class SpinState : public IState
{
public:
    SpinState(std::chrono::milliseconds maxDuration);

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine) override;

    virtual const char* GetDebugName() const override { return "Spin"; }

    virtual ~SpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_maxEndTime;
};

#endif