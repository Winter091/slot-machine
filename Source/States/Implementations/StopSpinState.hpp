#ifndef _STOP_SPIN_STATE_H_
#define _STOP_SPIN_STATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

#include <chrono>

class StopSpinState final : public IState
{
public:
    StopSpinState(const std::vector<SlotRow>& rows, std::chrono::milliseconds minDuration);

    virtual IState* OnEvent(SlotMachine& slotMachine, const IEvent& input) override;
    virtual IState* Update(SlotMachine& slotMachine, float dt) override;
    virtual inline EStateName GetName() const override { return EStateName::StopSpin; }

    virtual ~StopSpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_startTime;

    std::vector<float> m_startSpeeds;
    std::vector<float> m_stopDurationsMs;
    std::vector<float> m_startPositions;
    std::vector<float> m_distToTravel;
    std::vector<bool> m_alreadyStopped;
    int m_numRunning;
};

#endif