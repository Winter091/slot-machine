#include "IdleState.hpp"

#include <iostream>

void IdleState::HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event)
{
    (void)slotMachine;
    (void)event;
}

void IdleState::Update(SlotMachine* slotMachine)
{
    (void)slotMachine;
}

IdleState::~IdleState()
{

}