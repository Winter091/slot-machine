#include "SlotMachine.hpp"

#include "SlotRow.hpp"

SlotMachine::SlotMachine(std::vector<SlotRow> slotRows)
    : m_slotRows(slotRows)
{}

SlotMachine SlotMachine::NewRandom(uint32_t numRows, uint32_t numInRow)
{
    std::vector<SlotRow> rows;
    rows.reserve(numRows);

    for (uint32_t i = 0; i < numRows; i++) {
        SlotRow s = SlotRow::NewRandom(numInRow);
        rows.push_back(s);
    }

    return SlotMachine(rows);
}