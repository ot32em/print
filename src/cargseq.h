#pragma once

#include "cstr.h"
#include "cbit.h"

using seq_t = unsigned long long;

constexpr seq_t any_arg_seq(
    cstr str, char escape='%', char id='%', unsigned int count_arg = 0, unsigned int i=0)
{
    /****
     *   Hello %s, I'm %s. I have 23.0%% fat rate.
     *         ^-      ^-             ^-
     */
    return i >= str.length()?
            0:
            str[i] != escape?
                any_arg_seq(str, escape, id, count_arg, i+1): // non % case, advance to next i.
                i + 1 >= str.length()?
                    any_arg_seq(str, escape, id, count_arg, i+1): // only one % at tail. ignore it
                    str[i + 1] == escape?
                        any_arg_seq(str, escape, id, count_arg, i+2): // jump over %%
                        id == escape? ( // any_arg will reconginize any symbol with prefix %
                            bit_at(count_arg) | any_arg_seq(str, escape, id, count_arg + 1, i+2)
                        ):(
                            str[i+1] == id?
                                bit_at(count_arg) | any_arg_seq(str, escape, id, count_arg + 1, i+2):
                                any_arg_seq(str, escape, id, count_arg + 1, i+1) // bypass unknown arg id
                        );
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


constexpr std::size_t arg_pos_at(cstr msg, unsigned nth_arg, char escape = '%', unsigned i = 0)
{
    return 
        i == msg.length()? -1:
            i + 1 == msg.length()? -1:
                msg[i] != escape? arg_pos_at(msg, nth_arg, escape, i+1):
                    msg[i+1] == escape? arg_pos_at(msg, nth_arg, escape, i+2):
                        nth_arg != 0 ? arg_pos_at(msg, nth_arg - 1, escape, i+2):
                        i;
}
