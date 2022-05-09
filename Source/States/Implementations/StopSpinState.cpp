#include "StopSpinState.hpp"

#include "ShowResultsState.hpp"
#include <Source/Config.hpp>
#include <cmath>
#include <iostream>

using namespace std::chrono;
using namespace std::chrono_literals;

StopSpinState::StopSpinState(const std::vector<SlotRow>& rows, milliseconds minDuration)
    : m_alreadyStopped(rows.size(), false)
    , m_numRunning(rows.size())
{
    m_startSpeeds.reserve(rows.size());
    m_stopDurationsMs.reserve(rows.size());
    m_startPositions.reserve(rows.size());
    m_distsToTravel.reserve(rows.size());
    
    m_startTime = high_resolution_clock::now();

    for (const SlotRow& row : rows) {
        FillPerfectStopPosForRow(row, minDuration);
    }
}

void StopSpinState::FillPerfectStopPosForRow(const SlotRow& row, milliseconds minDuration)
{
    float dist = 0.5f * row.GetSpeed() * minDuration.count();
    float posAtEnd = row.GetPosition() + dist;

    float slotSize = 1.0f / row.GetSlots().size();
    float distToTop = row.DistanceToSlotTop(posAtEnd);
    float distToNextCenter = distToTop - slotSize / 2.0f;
    if (distToNextCenter < 0.0f) {
        distToNextCenter += slotSize;
    }

    float distToTravel = dist + distToNextCenter;

    m_startSpeeds.push_back(row.GetSpeed());
    m_startPositions.push_back(row.GetPosition());
    m_stopDurationsMs.push_back(2.0f * distToTravel / row.GetSpeed());
    m_distsToTravel.push_back(distToTravel);
}

IState* StopSpinState::OnEvent(SlotMachine& /*slotMachine*/, const IEvent& /*event*/)
{
    return nullptr;
}

IState* StopSpinState::Update(SlotMachine& slotMachine, float /*dt*/)
{
    auto& rows = slotMachine.GetRows();
    const auto currTime = high_resolution_clock::now();
    float durationMs = duration_cast<microseconds>(currTime - m_startTime).count() / 1000.0f;
    
    for (std::size_t i = 0; i < rows.size(); i++) {
        UpdateRow(rows[i], i, durationMs);
    }

    if (m_numRunning == 0) {
        return new ShowResultsState(slotMachine, milliseconds(cfg::SHOW_RESULTS_DURATION_MS));
    }

    return nullptr;
}

void StopSpinState::UpdateRow(SlotRow& row, std::size_t index, float durationMs)
{
    if (m_alreadyStopped[index]) {
        return;
    }

    if (durationMs < m_stopDurationsMs[index]) {
        UpdateRowSpeedAndPos(row, index, durationMs);
    } else {
        StopRow(row, index);
    }
}

void StopSpinState::UpdateRowSpeedAndPos(SlotRow& row, std::size_t index, float timeMs)
{
    float accel = -m_startSpeeds[index] / m_stopDurationsMs[index];
    float pos = m_startPositions[index] 
                + m_startSpeeds[index] * timeMs 
                + accel * timeMs * timeMs / 2;

    float speedMult = 1.0f - timeMs / m_stopDurationsMs[index];
    float speed = m_startSpeeds[index] * speedMult;
    
    row.SetSpeed(speed);
    row.SetPosition(pos);
}

void StopSpinState::StopRow(SlotRow& row, std::size_t index)
{
    row.SetSpeed(0.0f);
    row.SetPosition(m_startPositions[index] + m_distsToTravel[index]);

    m_alreadyStopped[index] = true;
    --m_numRunning;
}
