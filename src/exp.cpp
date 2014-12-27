#include "cstr.h"

constexpr char my_char() { return '1'; }

template <char c>
constexpr int val(std::size_t i);

template <>
constexpr int val<'1'>(std::size_t i) { return 1 + i; }

template <>
constexpr int val<'0'>(std::size_t i) { return 0 + i; }

constexpr int select(cstr str)
{
    return val<str[0]>(100);
}

int main()
{
    static_assert(val<'1'>(100) == 101, " should be 1");
    static_assert(val<'0'>(100) == 100, " should be 0");
    static_assert(val<my_char()>(100) == 101, " should be 1");
    static_assert(val<cstr("1001")[0]>(100)  == 101, "");
    return 0;
}
