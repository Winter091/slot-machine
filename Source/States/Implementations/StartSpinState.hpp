#ifndef _START_SPIN_STATE_H_
#define _START_SPIN_STATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

#include <chrono>
#include <vector>

class StartSpinState final : public IState
{
public:
    StartSpinState(int numRows, std::chrono::milliseconds duration);

    virtual IState* HandleEvent(SlotMachine& slotMachine, const IEvent& input) override;
    virtual IState* Update(SlotMachine& slotMachine, float dt) override;
    virtual inline EStateName GetName() const override { return EStateName::StartSpin; }

    virtual ~StartSpinState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_startTime;
    std::chrono::high_resolution_clock::time_point m_endTime;
    std::vector<float> m_rowDesiredSpeeds;
};

#endif