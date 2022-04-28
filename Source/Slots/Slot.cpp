#include "Slot.hpp"

#include <random>

Slot::Slot(ESlotType type)
    : m_type(type)
{}

Slot Slot::NewRandom()
{
    static std::random_device rd;
    static std::mt19937 e2(rd());
    static std::uniform_int_distribution<uint32_t> dist(0, (uint32_t)ESlotType::COUNT - 1);

    ESlotType randType = (ESlotType)dist(e2);
    return Slot(randType);
}
