#pragma once

struct ArgToken
{
    char type;
    std::size_t pos;
};

namespace symbol
{
    constexpr char Any() { return '*'; }
    constexpr char Str() { return 's'; }
    constexpr char Int() { return 'd'; }
    constexpr char Float() { return 'f'; }
    constexpr char Esc() { return '%'; }
    constexpr char Unknown() { return '?'; }
}

constexpr const char* EscAsString() { return "%"; }
