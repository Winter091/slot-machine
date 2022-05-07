#include "ShowResultsState.hpp"

#include "IdleState.hpp"

using namespace std::chrono;

ShowResultsState::ShowResultsState(SlotMachine& slotMachine, milliseconds duration)
    : m_endTime(high_resolution_clock::now() + duration)
{
    slotMachine.RecalcWinStatus();
}

IState* ShowResultsState::HandleButtonEvent(SlotMachine& /* slotMachine */, const ButtonEvent& /* event */)
{
    return nullptr;
}

IState* ShowResultsState::Update(SlotMachine& /*slotMachine*/, float /*dt*/)
{
    if (high_resolution_clock::now() > m_endTime) {
        return new IdleState();
    }

    return nullptr;
}