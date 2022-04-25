#include "SlotRow.hpp"

SlotRow::SlotRow(const std::vector<Slot>& slots)
    : m_slots(slots)
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