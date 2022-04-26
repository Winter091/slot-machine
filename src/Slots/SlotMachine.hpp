#ifndef _SLOTMACHINE_H_
#define _SLOTMACHINE_H_

#include "SlotRow.hpp"
#include <src/States/IState.hpp>

#include <vector>
#include <memory>

class SlotMachine
{
public:
    SlotMachine(std::vector<SlotRow> slotRows);
    static SlotMachine* NewRandom(uint32_t numRows, uint32_t numInRow);

    void Update();

private:
    std::vector<SlotRow> m_slotRows;
    IState* m_state;
};

#endif