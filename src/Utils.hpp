#ifndef _UTILS_H_
#define _UTILS_H_

inline static int WrapInt(int num, int const lower, int const upper)
{
    int range_size = upper - lower + 1;

    if (num < lower)
        num += range_size * ((lower - num) / range_size + 1);

    return lower + (num - lower) % range_size;
}

#endif