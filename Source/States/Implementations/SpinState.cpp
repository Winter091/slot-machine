#include "SpinState.hpp"

#include "StopSpinState.hpp"
#include <Source/Config.hpp>
#include <Source/Events/Implementations/ButtonEvent.hpp>

using namespace std::chrono;

SpinState::SpinState(milliseconds maxDuration)
{
    m_maxEndTime = high_resolution_clock::now() + maxDuration;
}

IState* SpinState::HandleEvent(SlotMachine& slotMachine, const IEvent& event)
{
    if (event.GetEventType() != EEventType::Button) {
        return nullptr;
    }

    const ButtonEvent& buttonEvent = dynamic_cast<const ButtonEvent&>(event);
    
    if (buttonEvent.GetButtonAction() != EButtonAction::Press) {
        return nullptr;
    }

    switch (buttonEvent.GetButtonType()) {
        case EButtonType::Stop:
            return new StopSpinState(slotMachine.GetRows(), milliseconds(cfg::STOP_MIN_DURATION_MS));
            break;
        default:
            break;
    }

    return nullptr;
}

IState* SpinState::Update(SlotMachine& slotMachine, float dt)
{   
    slotMachine.MoveAllRows(dt);
    
    if (high_resolution_clock::now() > m_maxEndTime) {
        return new StopSpinState(slotMachine.GetRows(), milliseconds(cfg::STOP_MIN_DURATION_MS));
    }

    return nullptr;
}
