#pragma once

#include <limits>

constexpr unsigned long long bit_at(unsigned char n)
{
    return 1LLU << n;
}

template <typename... PositionT>
constexpr unsigned long long bit_at(unsigned char n, PositionT... posn)
{
    return 0;
}

constexpr unsigned short count_bit1(unsigned long long bits, unsigned short c = 0)
{
    return !bits? c: count_bit1(bits >> 1, c + (bits & 1)); 
}

constexpr unsigned short count_bit0(unsigned long long bits)
{
    return count_bit1(bits ^ std::numeric_limits<unsigned long long>::max());
}

