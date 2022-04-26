#ifndef _SLOTMACHINE_H_
#define _SLOTMACHINE_H_

#include "SlotRow.hpp"

#include <vector>

class SlotMachine
{
public:
    SlotMachine(std::vector<SlotRow> slotRows);

    static SlotMachine NewRandom(uint32_t numRows, uint32_t numInRow);

private:
    std::vector<SlotRow> m_slotRows;
};

#endif