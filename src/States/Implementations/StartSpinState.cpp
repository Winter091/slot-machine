#include "StartSpinState.hpp"

#include "SpinState.hpp"

#include <random>

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

    m_rowDesiredSpeeds = GetRandFloats(numRows, 0.0002f, 0.0003f);
}

IState* StartSpinState::HandleButtonEvent(SlotMachine* slotMachine, const ButtonEvent& event)
{
    (void)slotMachine;
    (void)event;
    return nullptr;
}

IState* StartSpinState::Update(SlotMachine* slotMachine)
{
    auto allDuration = m_endTime - m_startTime;
    auto currDuration = std::chrono::high_resolution_clock::now() - m_startTime;
    float part = (float)currDuration.count() / allDuration.count();

    if (part >= 1.0f) {
        auto& rows = slotMachine->GetRows();
        for (std::size_t i = 0; i < m_rowDesiredSpeeds.size(); i++) {
            rows[i].GetSpeed() = m_rowDesiredSpeeds[i];
        }

        using namespace std::chrono_literals;
        return new SpinState(15s);
    }

    auto& rows = slotMachine->GetRows();
    for (std::size_t i = 0; i < m_rowDesiredSpeeds.size(); i++) {
        rows[i].GetSpeed() = m_rowDesiredSpeeds[i] * part;
    }
    return nullptr;
}
