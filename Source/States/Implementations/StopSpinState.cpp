#include "StopSpinState.hpp"

#include "IdleState.hpp"
#include <cmath>
#include <iostream>

using namespace std::chrono_literals;

StopSpinState::StopSpinState(const std::vector<SlotRow>& rows, std::chrono::milliseconds minDuration)
    : m_startRowSpeeds(rows.size())
    , m_stopTimes(rows.size())
    , m_alreadyStopped(rows.size(), false)
    , m_numRunning(rows.size())
{
    m_startTime = std::chrono::high_resolution_clock::now();

    // For each row, based on its speed, calculate time
    // required to stop perfectly at some future slot's center
    for (std::size_t i = 0; i < rows.size(); i++) {
        const auto& row = rows[i];

        float dist = 0.5f * row.GetSpeed() * minDuration.count();
        float posNow = row.GetPosition();
        float posAtEnd = std::fmod(posNow + dist, 1.0f);

        float slotSize = 1.0f / row.GetSlots().size();
        float distToTop = row.DistanceToSlotTop(posAtEnd);
        float distToNextCenter = distToTop - slotSize / 2.0f;
        if (distToNextCenter < 0.0f) {
            distToNextCenter += slotSize;
        }

        if (posAtEnd < posNow) {
            posAtEnd += 1.0f;
        }
        float baseDist = posAtEnd - posNow;

        float newTimeMs = 2.0f * (baseDist + distToNextCenter) / row.GetSpeed();
        m_stopTimes[i] = std::chrono::milliseconds(static_cast<int>(newTimeMs));
    }

    for (std::size_t i = 0; i < rows.size(); i++) {
        m_startRowSpeeds[i] = rows[i].GetSpeed();
    }
}

IState* StopSpinState::HandleButtonEvent(SlotMachine* /*slotMachine*/, const ButtonEvent& /*event*/)
{
    return nullptr;
}

IState* StopSpinState::Update(SlotMachine* slotMachine, float dt)
{
    using namespace std::chrono;

    auto& rows = slotMachine->GetRows();

    const auto currTime = high_resolution_clock::now();
    
    for (std::size_t i = 0; i < rows.size(); i++) {
        if (m_alreadyStopped[i]) {
            continue;
        }

        auto& row = rows[i];

        const auto currDuration = duration_cast<milliseconds>(currTime - m_startTime);
        float part = (float)currDuration.count() / m_stopTimes[i].count();

        if (part < 1.0f) {
            row.SetSpeed(m_startRowSpeeds[i] * (1.0f - part));
        } else {
            m_alreadyStopped[i] = true;
            --m_numRunning;
            row.SetSpeed(0.0f);
        }
    }

    for (auto& row : slotMachine->GetRows()) {
        row.Move(row.GetSpeed() * dt);
    }

    if (m_numRunning == 0) {
        return new IdleState();
    }

    return nullptr;
}
