#ifndef _SLOT_H_
#define _SLOT_H_

#include "ESlotType.hpp"

class Slot
{
public:
    Slot(ESlotType type = ESlotType::ONE);
    static Slot NewRandom();

    ESlotType GetType() const { return m_type; }

private:
    ESlotType m_type;
};

#endif