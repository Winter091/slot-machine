#include "IdleState.hpp"

#include "StartSpinState.hpp"
#include <Source/Config.hpp>
#include <Source/Events/Implementations/ButtonEvent.hpp>

IState* IdleState::HandleEvent(SlotMachine& slotMachine, const IEvent& event)
{
    if (event.GetEventType() != EEventType::Button) {
        return nullptr;
    }

    const ButtonEvent& buttonEvent = dynamic_cast<const ButtonEvent&>(event);
    
    if (buttonEvent.GetButtonAction() != EButtonAction::Press) {
        return nullptr;
    }

    switch (buttonEvent.GetButtonType()) {
        case EButtonType::Start:
            return new StartSpinState(
                slotMachine.GetRows().size(), 
                std::chrono::milliseconds(cfg::START_SPIN_DURATION_MS)
            );
        default:
            break;
    }

    return nullptr;
}

IState* IdleState::Update(SlotMachine& /*slotMachine*/, float /*dt*/)
{
    return nullptr;
}
