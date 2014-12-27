#pragma once

#include <limits>

using seq_t = unsigned long long;

constexpr seq_t bit_at(unsigned char n)
{
    return 1LLU << n;
}

template <typename... PositionT>
constexpr seq_t bit_at(unsigned char n, PositionT... poses)
{
    return bit_at(n) | bit_at(poses...);
}

constexpr unsigned short count_bit1(seq_t bits, unsigned short c = 0)
{
    return !bits? c: count_bit1(bits >> 1, c + (bits & 1)); 
}

constexpr unsigned short count_bit0(seq_t bits)
{
    return count_bit1(bits ^ std::numeric_limits<seq_t>::max());
}

