#include "StopSpinState.hpp"

#include "ShowResultsState.hpp"
#include <Source/Config.hpp>
#include <cmath>
#include <iostream>

using namespace std::chrono_literals;

StopSpinState::StopSpinState(const std::vector<SlotRow>& rows, std::chrono::milliseconds minDuration)
    : m_startSpeeds(rows.size())
    , m_stopDurationsMs(rows.size())
    , m_startPositions(rows.size())
    , m_distToTravel(rows.size())
    , m_alreadyStopped(rows.size())
    , m_numRunning(rows.size())
{
    m_startTime = std::chrono::high_resolution_clock::now();

    // Calculate distance to travel to stop perfectly at some
    // future's slot's center and time required to do it 
    for (std::size_t i = 0; i < rows.size(); i++) {
        const auto& row = rows[i];

        float dist = 0.5f * row.GetSpeed() * minDuration.count();
        float posNow = row.GetPosition();
        float posAtEnd = posNow + dist;

        float slotSize = 1.0f / row.GetSlots().size();
        float distToTop = row.DistanceToSlotTop(posAtEnd);
        float distToNextCenter = distToTop - slotSize / 2.0f;
        if (distToNextCenter < 0.0f) {
            distToNextCenter += slotSize;
        }

        float distToTravel = dist + distToNextCenter;
        m_startPositions[i] = posNow;
        m_distToTravel[i] = distToTravel;
        m_stopDurationsMs[i] = 2.0f * distToTravel / row.GetSpeed();
    }

    for (std::size_t i = 0; i < rows.size(); i++) {
        m_startSpeeds[i] = rows[i].GetSpeed();
    }
}

IState* StopSpinState::HandleEvent(SlotMachine& /*slotMachine*/, const IEvent& /*event*/)
{
    return nullptr;
}

IState* StopSpinState::Update(SlotMachine& slotMachine, float /* dt */)
{
    using namespace std::chrono;

    auto& rows = slotMachine.GetRows();

    const auto currTime = high_resolution_clock::now();
    
    for (std::size_t i = 0; i < rows.size(); i++) {
        if (m_alreadyStopped[i]) {
            continue;
        }

        auto& row = rows[i];

        float timeMs = duration_cast<microseconds>(currTime - m_startTime).count() / 1000.0f;
        float part = timeMs / m_stopDurationsMs[i];

        // Setting speed is not required (position is being set directly),
        // but it's good to do nontheless 
        if (part < 1.0f) {
            const float accel = -m_startSpeeds[i] / m_stopDurationsMs[i];
            float pos = m_startPositions[i] 
                        + m_startSpeeds[i] * timeMs 
                        + accel * timeMs * timeMs / 2;
            
            row.SetSpeed(m_startSpeeds[i] * (1.0f - part));
            row.SetPosition(pos);
        } else {
            m_alreadyStopped[i] = true;
            --m_numRunning;
            row.SetSpeed(0.0f);
            row.SetPosition(m_startPositions[i] + m_distToTravel[i]);
        }
    }

    if (m_numRunning == 0) {
        return new ShowResultsState(slotMachine, milliseconds(cfg::SHOW_RESULTS_DURATION_MS));
    }

    return nullptr;
}
