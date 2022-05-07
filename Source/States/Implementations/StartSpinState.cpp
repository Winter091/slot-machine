#include "StartSpinState.hpp"

#include "SpinState.hpp"
#include "Source/Utils.hpp"
#include <Source/Config.hpp>

using namespace std::chrono;
using namespace std::chrono_literals;

StartSpinState::StartSpinState(int numRows, milliseconds duration)
{
    m_startTime = high_resolution_clock::now();
    m_endTime = m_startTime + duration;

    m_rowDesiredSpeeds = GetRandFloats(numRows, cfg::MIN_ROW_SPEED, cfg::MAX_ROW_SPEED);
}

IState* StartSpinState::OnEvent(SlotMachine& /*slotMachine*/, const IEvent& /*event*/)
{
    return nullptr;
}

IState* StartSpinState::Update(SlotMachine& slotMachine, float dt)
{
    auto allDuration = m_endTime - m_startTime;
    auto currDuration = high_resolution_clock::now() - m_startTime;
    float part = (float)currDuration.count() / allDuration.count();

    IState* ret = nullptr;
    auto& rows = slotMachine.GetRows();

    if (part >= 1.0f) {
        for (std::size_t i = 0; i < m_rowDesiredSpeeds.size(); i++) {
            rows[i].SetSpeed(m_rowDesiredSpeeds[i]);
        }
        ret = new SpinState(milliseconds(cfg::SPIN_MAX_DURATION_MS));
    } else {
        for (std::size_t i = 0; i < m_rowDesiredSpeeds.size(); i++) {
            rows[i].SetSpeed(m_rowDesiredSpeeds[i] * part);
        }
    }

    slotMachine.MoveAllRows(dt);
    
    return ret;
}
