#include "Slot.hpp"

#include <cstdlib>

Slot::Slot(ESlotType type)
    : m_type(type)
{}

Slot Slot::NewRandom()
{
    uint32_t index = std::rand() % (uint32_t)ESlotType::COUNT;
    ESlotType randType = (ESlotType)index;
    return Slot(randType);
}
