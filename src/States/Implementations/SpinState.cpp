#include "SpinState.hpp"

#include "StopSpinState.hpp"

using namespace std::chrono_literals;

SpinState::SpinState(std::chrono::milliseconds maxDuration)
{
    m_maxEndTime = std::chrono::high_resolution_clock::now() + maxDuration;
}

IState* SpinState::HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event)
{
    if (event.GetAction() != EButtonAction::Press) {
        return nullptr;
    }

    switch (event.GetType()) {
        case EButtonType::Stop:
            return new StopSpinState(slotMachine->GetRows(), 500ms);
            break;
        default:
            break;
    }

    return nullptr;
}

IState* SpinState::Update(SlotMachine* slotMachine)
{
    if (std::chrono::high_resolution_clock::now() > m_maxEndTime) {
        return new StopSpinState(slotMachine->GetRows(), 500ms);
    }

    return nullptr;
}
