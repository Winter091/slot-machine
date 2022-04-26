#ifndef _STOPSPINSTATE_H_
#define _STOPSPINSTATE_H_

#include <src/States/IState.hpp>
#include <src/Slots/SlotMachine.hpp>

#include <chrono>

class StopSpinState : public IState
{
public:
    StopSpinState(const std::vector<SlotRow>& rows, std::chrono::milliseconds duration);

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine) override;

    virtual ~StopSpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_endTime;
    std::vector<float> m_startRowSpeeds;
};

#endif