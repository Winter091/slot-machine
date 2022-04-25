#ifndef _SLOTROW_H_
#define _SLOTROW_H_

#include "Slot.hpp"

#include <vector>

class SlotRow
{
public:
    SlotRow(const std::vector<Slot>& slots);

    static SlotRow NewRandom(uint32_t size);

private:
    std::vector<Slot> m_slots;
};

#endif