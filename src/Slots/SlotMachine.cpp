#include "SlotMachine.hpp"

#include "SlotRow.hpp"
#include <src/States/Implementations/IdleState.hpp>

#include <cassert>
#include <iostream>
#include <unordered_map>

SlotMachine::SlotMachine(const std::vector<SlotRow>& slotRows)
    : m_slotRows(slotRows)
    , m_state(new IdleState())
{}

SlotMachine* SlotMachine::NewRandom(uint32_t numRows, uint32_t numInRow)
{
    std::vector<SlotRow> rows;
    rows.reserve(numRows);
    
    for (uint32_t i = 0; i < numRows; i++) {
        SlotRow s = SlotRow::NewRandom(numInRow);
        rows.push_back(s);
    }

    return new SlotMachine(rows);
}

void SlotMachine::HandleButtonEvent(const ButtonEvent& event)
{
    assert(m_state && "State pointer is nullptr");

    IState* newState = m_state->HandleButtonEvent(this, event);
    if (newState) {
        SetState(newState);
    }
}

void SlotMachine::Update(float dt)
{
    assert(m_state && "State pointer is nullptr");

    IState* newState = m_state->Update(this, dt);
    if (newState) {
        SetState(newState);
    }
}

void SlotMachine::SetState(IState* newState)
{
    delete m_state;
    m_state = newState;
}