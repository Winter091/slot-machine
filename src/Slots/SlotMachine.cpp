#include "SlotMachine.hpp"

#include "SlotRow.hpp"
#include <src/States/Implementations/IdleState.hpp>

#include <cassert>
#include <iostream>
#include <unordered_map>

SlotMachine::SlotMachine(std::vector<SlotRow> slotRows)
    : m_slotRows(slotRows)
    , m_state(new IdleState())
{}

SlotMachine* SlotMachine::NewRandom(uint32_t numRows, uint32_t numInRow)
{
    std::vector<SlotRow> rows;
    rows.reserve(numRows);

    std::unordered_map<ESlotType, int> types = {
        { ESlotType::ONE, 1 },
        { ESlotType::TWO, 2 },
        { ESlotType::THREE, 3 },
    };

    for (uint32_t i = 0; i < numRows; i++) {
        SlotRow s = SlotRow::NewRandom(numInRow);
        rows.push_back(s);
        // for (const auto& elem : s.GetSlots()) {
        //     std::cout << types[elem.GetType()] << ' ';
        // }
        // std::cout << '\n';
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

    IState* newState = m_state->Update(this);
    if (newState) {
        SetState(newState);
    }

    for (auto& row : m_slotRows) {
        row.Move(row.GetSpeed() * dt);
    }
}

void SlotMachine::SetState(IState* newState)
{
    delete m_state;
    m_state = newState;
}