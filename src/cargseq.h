#pragma once

#include "cstr.h"
#include "cbit.h"
#include "ArgType.h"


constexpr seq_t 
arg_seq(cstr str, char arg_c = Symbol::Any(), char esc_c = Symbol::Esc(), unsigned int found_args = 0, unsigned int i = 0)
{
    return
        i >= str.length() || i + 1 >= str.length()?
            0ULL // end of analyze
        : str[i] != esc_c?
            // non arg, pass it
            arg_seq(str, arg_c, esc_c, found_args, i + 1)
        : arg_c == Symbol::Any()?
            // detected a arg, includes it
            bit_at(found_args) | arg_seq(str, arg_c, esc_c, found_args + 1, i + 2)
        : str[i + 1] == arg_c?
            // detected specific arg, includes it
            bit_at(found_args) | arg_seq(str, arg_c, esc_c, found_args + 1, i + 2)
        :
            // detected other arg, pass it
            arg_seq(str, arg_c, esc_c, found_args + 1, i + 2);
}

constexpr std::size_t pos_of_nth_arg(cstr msg, unsigned nth_arg, char esc_c = Symbol::Esc(), unsigned i = 0)
{
    return
        i == msg.length() || i + 1 == msg.length()?
            -1 // end of string
        : msg[i] != esc_c?
            pos_of_nth_arg(msg, nth_arg, esc_c, i + 1) // normal char, move on
        : nth_arg != 0 ?
            pos_of_nth_arg(msg, nth_arg - 1, esc_c, i + 2) // detected arg, not the nth, continue
        :
            i; // detected nth arg
}

constexpr char arg_type_at_bit(unsigned bit_i){
    return '?';
}

template<typename... seq_ts>
constexpr char arg_type_at_bit(unsigned bit_i, seq_t test_seq, char seq_c, seq_ts... other_seqs) {
    return (test_seq & bit_at(bit_i))? seq_c: arg_type_at_bit(bit_i, other_seqs...);
}
