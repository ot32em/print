#pragma once
#include "cstr.h"
#include "cargseq.h"

constexpr char arg_type_at_bit(unsigned bit_i){
    return '?';
}

template<typename... seq_ts> 
constexpr char arg_type_at_bit(unsigned bit_i, seq_t test_seq, char seq_c, seq_ts... other_seqs) {
    return (test_seq & bit_at(bit_i))? seq_c: arg_type_at_bit(bit_i, other_seqs...);
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
        seq_t all_seq = any_arg_seq(msg, '%', '*');
        seq_t str_seq = str_arg_seq(msg);
        seq_t int_seq = int_arg_seq(msg);
        seq_t float_seq = float_arg_seq(msg);
        seq_t escape_seq = any_arg_seq(msg, '%', '%');

        arg_infos_.resize(count_bit1(all_seq));
        for(std::size_t i = 0; i < arg_infos_.size(); i++)
        {
            arg_infos_[i].type = arg_type_at_bit(i, str_seq, 's', int_seq, 'd', float_seq, 'f', escape_seq, '%');
            arg_infos_[i].pos = pos_of_nth_arg(msg, i);
        }
    }

    std::size_t count_args(char arg_s='*') const
    {
        if(arg_s == '*') return arg_infos_.size();
        return std::count_if(arg_infos_.begin(), arg_infos_.end(), 
                [arg_s](ArgInfo ai){ return ai.type == arg_s; });
    };

    ArgInfo operator[](std::size_t i) const
    {
        return arg_infos_.at(i);
    }

    std::vector<ArgInfo>::iterator begin() { return arg_infos_.begin(); }
    std::vector<ArgInfo>::iterator end() { return arg_infos_.end(); }

    std::vector<ArgInfo>::const_iterator begin() const { return arg_infos_.begin(); }
    std::vector<ArgInfo>::const_iterator end() const { return arg_infos_.end(); }

private:
    cstr msg_;
    std::vector<ArgInfo> arg_infos_;
};


