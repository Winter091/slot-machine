#ifndef _STOPSPINSTATE_H_
#define _STOPSPINSTATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

#include <chrono>

class StopSpinState final : public IState
{
public:
    StopSpinState(const std::vector<SlotRow>& rows, std::chrono::milliseconds minDuration);

    virtual IState* HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine* slotMachine, float dt) override;

    virtual ~StopSpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_startTime;

    std::vector<float> m_startRowSpeeds;
    std::vector<std::chrono::milliseconds> m_stopTimes;
    std::vector<bool> m_alreadyStopped;
    int m_numRunning;
};

#endif