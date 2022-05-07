#include "ShowResultsState.hpp"

#include "IdleState.hpp"
#include <Source/Events/Implementations/ButtonEvent.hpp>


using namespace std::chrono;

ShowResultsState::ShowResultsState(SlotMachine& slotMachine, milliseconds duration)
    : m_endTime(high_resolution_clock::now() + duration)
{
    slotMachine.RecalcWinStatus();
}

IState* ShowResultsState::OnEvent(SlotMachine& /* slotMachine */, const IEvent& event)
{
    if (event.GetEventType() != EEventType::Button) {
        return nullptr;
    }

    const ButtonEvent& buttonEvent = dynamic_cast<const ButtonEvent&>(event);

    if (buttonEvent.GetButtonAction() != EButtonAction::Press) {
        return nullptr;
    }

    // Skip win status message
    if (buttonEvent.GetButtonType() == EButtonType::WinMessage) {
        return new IdleState();
    }

    return nullptr;
}

IState* ShowResultsState::Update(SlotMachine& /*slotMachine*/, float /*dt*/)
{
    if (high_resolution_clock::now() > m_endTime) {
        return new IdleState();
    }

    return nullptr;
}
