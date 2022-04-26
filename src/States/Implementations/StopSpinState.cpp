#include "StopSpinState.hpp"

#include "IdleState.hpp"

using namespace std::chrono_literals;

StopSpinState::StopSpinState(const std::vector<SlotRow>& rows, std::chrono::milliseconds duration)
{
    m_startTime = std::chrono::high_resolution_clock::now();
    m_endTime = m_startTime + duration;

    m_startRowSpeeds.reserve(rows.size());
    for (auto& row : rows) {
        m_startRowSpeeds.push_back(row.GetSpeed());
    }
}

IState* StopSpinState::HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event)
{
    (void)slotMachine;
    (void)event;
    return nullptr;
}

IState* StopSpinState::Update(SlotMachine* slotMachine)
{
    auto allDuration = m_endTime - m_startTime;
    auto currDuration = std::chrono::high_resolution_clock::now() - m_startTime;
    float part = (float)currDuration.count() / allDuration.count();

    if (part >= 1.0f) {
        for (auto& row : slotMachine->GetRows()) {
            row.GetSpeed() = 0.0f;
        }

        return new IdleState();
    }

    auto& rows = slotMachine->GetRows();
    for (std::size_t i = 0; i < rows.size(); i++) {
        rows[i].GetSpeed() = m_startRowSpeeds[i] * (1.0f - part);
    }
    return nullptr;
}
