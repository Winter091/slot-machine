#include "IdleState.hpp"

#include "StartSpinState.hpp"
#include <Source/Config.hpp>

IState* IdleState::HandleButtonEvent(SlotMachine& slotMachine, const ButtonEvent& event)
{
    if (event.GetAction() != EButtonAction::Press) {
        return nullptr;
    }

    using namespace std::chrono;
    using namespace std::chrono_literals;

    switch (event.GetType()) {
        case EButtonType::Start:
            return new StartSpinState(slotMachine.GetRows().size(), 
                milliseconds(cfg::START_SPIN_DURATION_MS));
        default:
            break;
    }

    return nullptr;
}

IState* IdleState::Update(SlotMachine& /*slotMachine*/, float /*dt*/)
{
    return nullptr;
}
