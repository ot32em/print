#include <limits>

constexpr unsigned long long nth_bit(unsigned char n)
{
    return n? 1 << (n - 1): 0;
}

constexpr unsigned short bit1_count(unsigned long long bits, unsigned short c = 0)
{
    return !bits? c: bit1_count(bits >> 1, c + (bits & 1)); 
}

constexpr unsigned short bit0_count(unsigned long long bits)
{
    return bit1_count(bits ^ std::numeric_limits<unsigned long long>::max());
}

