#pragma once

#include <stdexcept>
#include <algorithm>
#include "cbit.h"
#include "cstr.h"

constexpr seq_t bits_from_str(cstr str, std::size_t i = 0)
{
    return 
        i == str.size()?
            0
        :str[str.size() - i - 1] == '0'?
            bits_from_str(str, i + 1)
        :str[str.size() - i - 1] == '1'?
            bit_at(i) | bits_from_str(str, i + 1)
        :
            throw std::invalid_argument("bits_from_str only accept cstr within 0 or 1 char.");
}

void fill_from_bits(char (&s)[65], seq_t bits)
{
    std::fill(std::begin(s), std::end(s)-1, '0');
    for(std::size_t i = 0; bits; bits >>= 1) 
    {
        if(bits & 1) { s[63 - i] = '1'; }
        i++;
    }
}
