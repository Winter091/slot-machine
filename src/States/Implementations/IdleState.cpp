#include "IdleState.hpp"

#include "StartSpinState.hpp"

IState* IdleState::HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event)
{
    if (event.GetAction() != EButtonAction::Press) {
        return nullptr;
    }

    using namespace std::chrono_literals;

    switch (event.GetType()) {
        case EButtonType::Start:
            return new StartSpinState(slotMachine->GetRows().size(), 1s);
            break;
        default:
            break;
    }

    return nullptr;
}

IState* IdleState::Update(SlotMachine* slotMachine)
{
    (void)slotMachine;
    return nullptr;
}
