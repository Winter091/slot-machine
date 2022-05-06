#ifndef _ESTATE_NAME_H_
#define _ESTATE_NAME_H_

#include <cstdint>

enum class EStateName : uint32_t
{
    Idle,
    StartSpin,
    Spin,
    StopSpin,
    ShowResults,
};

#endif