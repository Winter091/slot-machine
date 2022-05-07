#include "SlotMachine.hpp"

#include "SlotRow.hpp"
#include <Source/States/Implementations/IdleState.hpp>
#include <Source/Events/EventQueue.hpp> 
#include <Source/Events/Implementations/StateChangedEvent.hpp> 

#include <cassert>
#include <iostream>
#include <unordered_map>

SlotMachine::SlotMachine(const std::vector<SlotRow>& slotRows)
    : m_slotRows(slotRows)
    , m_state(std::make_unique<IdleState>())
    , m_hasWon(false)
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

void SlotMachine::OnEvent(const IEvent& event)
{
    assert(m_state && "State pointer is nullptr");

    IState* newState = m_state->OnEvent(*this, event);
    if (newState) {
        SetState(newState);
    }
}

void SlotMachine::Update(float dt)
{
    assert(m_state && "State pointer is nullptr");

    IState* newState = m_state->Update(*this, dt);
    if (newState) {
        SetState(newState);
    }
}

void SlotMachine::MoveAllRows(float dt)
{
    for (auto& row : m_slotRows) {
        row.Move(row.GetSpeed() * dt);
    }
}

void SlotMachine::RecalcWinStatus()
{
    m_hasWon = true;

    ESlotType prevSlot;
    bool hasValue = false;
    
    for (const auto& row : m_slotRows) {
        ESlotType slot = row.SlotFromPosition(row.GetPosition());
        
        if (!hasValue) {
            prevSlot = slot;
            hasValue = true;
            continue;
        }

        if (slot != prevSlot) {
            m_hasWon = false;
            break;
        }

        prevSlot = slot;
    }
}

void SlotMachine::SetState(IState* newState)
{
    assert(m_state && newState);
    
    EventQueue::AddEvent(std::unique_ptr<IEvent>(
        new StateChangedEvent(m_state->GetName(), newState->GetName())
    ));

    m_state.reset(newState);
}