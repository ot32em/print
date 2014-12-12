#pragma once

#include "cstr.h"
#include "cbit.h"

constexpr unsigned long long arg_seq(
    cstr str, char escape='%', char id='%', unsigned int count_arg = 0, unsigned int i=0)
{
    /****
     *   Hello %s, I'm %s. I have 23.0%% fat rate.
     *         ^-      ^-             ^-
     */
    return i >= str.length()?
            0:
            str[i] != escape?
                arg_seq(str, escape, id, count_arg, i+1): // non % case, advance to next i.
                i + 1 >= str.length()?
                    arg_seq(str, escape, id, count_arg, i+1): // only one % at tail. ignore it
                    str[i + 1] == escape?
                        arg_seq(str, escape, id, count_arg, i+2): // jump over %%
                        id == escape? (
                            bit_at(count_arg) | arg_seq(str, escape, id, count_arg + 1, i+2)
                        ):(
                            str[i+1] == id?
                                bit_at(count_arg) | arg_seq(str, escape, id, count_arg + 1, i+2):
                                arg_seq(str, escape, id, count_arg + 1, i+1) // bypass unknown arg id
                        );
}

constexpr unsigned long long 
str_arg_seq(cstr str, char escape='%')
{
    return arg_seq(str, escape, 's');
}

constexpr unsigned long long 
int_arg_seq(cstr str, char escape='%')
{
    return arg_seq(str, escape, 'd');
}

constexpr unsigned long long 
float_arg_seq(cstr str, char escape='%')
{
    return arg_seq(str, escape, 'f');
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
