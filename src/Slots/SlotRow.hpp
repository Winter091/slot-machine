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
    void Move(float posDelta);   
    
    void SetSpeed(float newSpeed) { m_speed = newSpeed; }
    float GetSpeed() const { return m_speed; }

    const std::vector<Slot>& GetSlots() const { return m_slots; }

    int IndexFromPosition(float pos) const;
    float DistanceToSlotTop(float pos) const;

private:
    std::vector<Slot> m_slots;
    float m_position;
    float m_speed;
};

#endif