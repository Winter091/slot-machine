#ifndef _STARTSPINSTATE_H_
#define _STARTSPINSTATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

#include <chrono>
#include <vector>

class StartSpinState final : public IState
{
public:
    StartSpinState(int numRows, std::chrono::milliseconds duration);

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine, float dt) override;

    virtual ~StartSpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_endTime;
    std::vector<float> m_rowDesiredSpeeds;
};

#endif