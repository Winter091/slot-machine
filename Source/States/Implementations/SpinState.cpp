#include "SpinState.hpp"

#include "StopSpinState.hpp"
#include <Source/Config.hpp>

using namespace std::chrono;
using namespace std::chrono_literals;

SpinState::SpinState(milliseconds maxDuration)
{
    m_maxEndTime = high_resolution_clock::now() + maxDuration;
}

IState* SpinState::HandleButtonEvent(SlotMachine& slotMachine, const ButtonEvent& event)
{
    if (event.GetAction() != EButtonAction::Press) {
        return nullptr;
    }

    switch (event.GetType()) {
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
    for (auto& row : slotMachine.GetRows()) {
        row.Move(row.GetSpeed() * dt);
    }
    
    if (high_resolution_clock::now() > m_maxEndTime) {
        return new StopSpinState(slotMachine.GetRows(), milliseconds(cfg::STOP_MIN_DURATION_MS));
    }

    return nullptr;
}
