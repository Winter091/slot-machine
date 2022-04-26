#ifndef _SLOTROW_H_
#define _SLOTROW_H_

#include "Slot.hpp"

#include <vector>

class SlotRow
{
public:
    SlotRow(const std::vector<Slot>& slots);
    static SlotRow NewRandom(uint32_t size);

    float GetPosition() const { return m_position; }
    float& GetSpeed() { return m_speed; }
    float GetSpeed() const { return m_speed; }
    
    void Move(float posDelta);   

private:
    std::vector<Slot> m_slots;
    float m_position;
    float m_speed;
};

#endif