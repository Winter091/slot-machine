#include "SlotRow.hpp"

#include <cmath>

SlotRow::SlotRow(const std::vector<Slot>& slots)
    : m_slots(slots)
    , m_position(0.0f)
    , m_speed(0.0f)
{}

SlotRow SlotRow::NewRandom(uint32_t size)
{
    std::vector<Slot> slots;
    slots.reserve(size);

    for (uint32_t i = 0; i < size; i++) {
        Slot s = Slot::NewRandom();
        slots.push_back(s);
    }

    return SlotRow(slots);
}

void SlotRow::Move(float posDelta)
{
    m_position = std::fmod(m_position + posDelta, 1.0f);
    if (m_position < 0.0f) {
        m_position += 1.0f;
    }
}

int SlotRow::IndexFromPosition(float pos) const
{
    float width = 1.0f / m_slots.size();
    pos = std::fmod(pos + width / 2.0f, 1.0f);

    return static_cast<int>(pos / width);
}

ESlotType SlotRow::SlotFromPosition(float pos) const
{
    int index = IndexFromPosition(pos);
    return m_slots[index].GetType();
}

float SlotRow::DistanceToSlotTop(float pos) const
{
    float width = 1.0f / m_slots.size();
    return width - std::fmod(pos + width / 2.0f, width);
}