#ifndef _SLOTMACHINE_H_
#define _SLOTMACHINE_H_

#include "SlotRow.hpp"
#include <src/States/IState.hpp>
#include <src/Buttons/Events/ButtonEvent.hpp>

#include <vector>
#include <memory>

class SlotMachine
{
public:
    SlotMachine(std::vector<SlotRow> slotRows);
    static SlotMachine* NewRandom(uint32_t numRows, uint32_t numInRow);

    void HandleButtonEvent(const ButtonEvent& event);
    void Update(float dt);

    std::vector<SlotRow>& GetRows() { return m_slotRows; }
    const std::vector<SlotRow>& GetRows() const { return m_slotRows; }
    
private:
    void SetState(IState* newState);

    std::vector<SlotRow> m_slotRows;
    IState* m_state;
};

#endif