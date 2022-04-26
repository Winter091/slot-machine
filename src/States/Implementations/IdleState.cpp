#include "IdleState.hpp"

#include <iostream>

void IdleState::HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& input)
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