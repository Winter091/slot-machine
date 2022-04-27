#include "StartSpinState.hpp"

#include "SpinState.hpp"

#include <random>

using namespace std::chrono_literals;

static std::vector<float> GetRandFloats(std::size_t vecSize, float low, float high)
{
    static std::random_device rd;
    static std::mt19937 e2(rd());
    std::uniform_real_distribution<float> dist(low, high);

    std::vector<float> vec(vecSize);
    for (float& elem : vec) {
        elem = dist(e2);
    }

    return vec;
}

StartSpinState::StartSpinState(int numRows, std::chrono::milliseconds duration)
{
    m_startTime = std::chrono::high_resolution_clock::now();
    m_endTime = m_startTime + duration;

    const float minRowSpeed = 0.0002f;
    const float maxRowSpeed = 0.0005f;
    m_rowDesiredSpeeds = GetRandFloats(numRows, minRowSpeed, maxRowSpeed);
}

IState* StartSpinState::HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event)
{
    (void)slotMachine;
    (void)event;
    return nullptr;
}

IState* StartSpinState::Update(SlotMachine* slotMachine, float dt)
{
    auto allDuration = m_endTime - m_startTime;
    auto currDuration = std::chrono::high_resolution_clock::now() - m_startTime;
    float part = (float)currDuration.count() / allDuration.count();

    IState* ret = nullptr;
    auto& rows = slotMachine->GetRows();

    if (part >= 1.0f) {
        for (std::size_t i = 0; i < m_rowDesiredSpeeds.size(); i++) {
            rows[i].SetSpeed(m_rowDesiredSpeeds[i]);
        }
        ret = new SpinState(15s);
    } else {
        for (std::size_t i = 0; i < m_rowDesiredSpeeds.size(); i++) {
            rows[i].SetSpeed(m_rowDesiredSpeeds[i] * part);
        }
    }

    for (auto& row : slotMachine->GetRows()) {
        row.Move(row.GetSpeed() * dt);
    }

    return ret;
}
