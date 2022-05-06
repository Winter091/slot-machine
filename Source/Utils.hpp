#ifndef _UTILS_H_
#define _UTILS_H_

#include <random>

inline static int WrapInt(int num, int const lower, int const upper)
{
    int range_size = upper - lower + 1;

    if (num < lower)
        num += range_size * ((lower - num) / range_size + 1);

    return lower + (num - lower) % range_size;
}

inline static std::vector<float> GetRandFloats(std::size_t vecSize, float low, float high)
{
    static std::random_device rd;
    static std::mt19937 e2(rd());
    std::uniform_real_distribution<float> dist(low, high);

    std::vector<float> vec(vecSize);
    for (float& elem : vec) {
        elem = dist(e2);
    }

    return vec;
}

#endif