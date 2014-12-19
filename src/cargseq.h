#pragma once

#include "cstr.h"
#include "cbit.h"

using seq_t = unsigned long long;

constexpr seq_t any_arg_seq(
    cstr str, char escape='%', char id='*', unsigned int count_arg = 0, unsigned int i=0)
{
    return
        i >= str.length() || i + 1 >= str.length()?
            0ULL // end of analyze
        : str[i] != escape?
            // non arg, pass it
            any_arg_seq(str, escape, id, count_arg, i+1)
        : id == '*'?
            // detected a arg, includes it
            bit_at(count_arg) | any_arg_seq(str, escape, id, count_arg + 1, i+2)
        : str[i+1] == id?
            // detected specific arg, includes it
            bit_at(count_arg) | any_arg_seq(str, escape, id, count_arg + 1, i+2)
        :
            // detected other arg, pass it
            any_arg_seq(str, escape, id, count_arg + 1, i+2);
}

constexpr seq_t str_arg_seq(cstr str, char escape='%')
{
    return any_arg_seq(str, escape, 's');
}

constexpr seq_t int_arg_seq(cstr str, char escape='%')
{
    return any_arg_seq(str, escape, 'd');
}

constexpr seq_t float_arg_seq(cstr str, char escape='%')
{
    return any_arg_seq(str, escape, 'f');
}


constexpr std::size_t pos_of_nth_arg(cstr msg, unsigned nth_arg, char escape = '%', unsigned i = 0)
{
    return
        i == msg.length() || i + 1 == msg.length()?
            -1 // end of string
        : msg[i] != escape?
            pos_of_nth_arg(msg, nth_arg, escape, i+1) // normal char, move on
        : nth_arg != 0 ?
            pos_of_nth_arg(msg, nth_arg - 1, escape, i+2) // detected arg, not the nth, continue
        :
            i; // detected nth arg
}
