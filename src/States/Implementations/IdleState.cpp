#include "IdleState.hpp"

#include <iostream>

void IdleState::HandleButtonInput(SlotMachine* slotMachine, const ButtonInput& input)
{
    (void)slotMachine;
    (void)input;
}

void IdleState::Update(SlotMachine* slotMachine)
{
    (void)slotMachine;
}

IdleState::~IdleState()
{

}