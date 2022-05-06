#ifndef _SHOW_RESULTS_STATE_H_
#define _SHOW_RESULTS_STATE_H_

#include <Source/States/IState.hpp>
#include <Source/Slots/SlotMachine.hpp>

#include <chrono>

class ShowResultsState final : public IState
{
public:
    ShowResultsState(SlotMachine& slotMachine, std::chrono::milliseconds duration);

    virtual IState* HandleButtonEvent(SlotMachine& slotMachine, const ButtonEvent& input) override;
    virtual IState* Update(SlotMachine& slotMachine, float dt) override;
    virtual inline EStateName GetName() const override { return EStateName::ShowResults; }

    virtual ~ShowResultsState() override {};

private:
    std::chrono::high_resolution_clock::time_point m_endTime;
};

#endif