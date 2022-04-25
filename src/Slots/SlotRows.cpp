#include "SlotRows.hpp"

#include "SlotRow.hpp"

SlotRows::SlotRows(std::vector<SlotRow> rows)
    : m_rows(rows)
{}

SlotRows SlotRows::NewRandom(uint32_t numRows, uint32_t numInRow)
{
    std::vector<SlotRow> rows;
    rows.reserve(numRows);

    for (uint32_t i = 0; i < numRows; i++) {
        SlotRow s = SlotRow::NewRandom(numInRow);
        rows.push_back(s);
    }

    return SlotRows(rows);
}