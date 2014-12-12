#pragma once
#include "cstr.h"
#include "cargseq.h"

constexpr char arg_type_at_bit(unsigned bit_i){
    return '?';
}

template<typename... seq_ts> 
constexpr char arg_type_at_bit(unsigned bit_i, seq_t test_seq, seq_ts... other_seqs) {
    return (test_seq & bit_at(bit_i))? 's': arg_type_at_bit(bit_i, other_seqs...);
}

class ArgParser
{public:
    struct ArgInfo
    {
        char type;
        std::size_t pos;
    };

    ArgParser(cstr msg)
        :msg_(msg)
    {
        seq_t all_seq = any_arg_seq(msg);
        seq_t str_seq = str_arg_seq(msg);
        seq_t int_seq = int_arg_seq(msg);
        seq_t float_seq = float_arg_seq(msg);

        arg_infos_.resize(count_bit1(all_seq));
        for(std::size_t i = 0; i < arg_infos_.size(); i++)
        {
            arg_infos_[i].type = arg_type_at_bit(i, str_seq, int_seq, float_seq);
            arg_infos_[i].pos = pos_of_nth_arg(msg, i);
        }
    }


    std::size_t count_args() const
    {
        return arg_infos_.size();
    };

    ArgInfo operator[](std::size_t i) const
    {
        return arg_infos_.at(i);
    }

private:
    cstr msg_;
    std::vector<ArgInfo> arg_infos_;
};


