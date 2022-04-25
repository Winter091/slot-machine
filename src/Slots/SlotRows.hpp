#ifndef _SLOTROWS_H_
#define _SLOTROWS_H_

#include "SlotRow.hpp"

#include <vector>

class SlotRows
{
public:
    SlotRows(std::vector<SlotRow> rows);

    static SlotRows NewRandom(uint32_t numRows, uint32_t numInRow);

private:
    std::vector<SlotRow> m_rows;
};

#endif