#pragma once
#include "cstr.h"
#include "cargseq.h"
#include "ArgType.h"

class ArgParser
{public:

    ArgParser(cstr msg)
        :msg_(msg)
    {
        seq_t all_seq = arg_seq(msg, symbol::Any());
        seq_t str_seq = arg_seq(msg, symbol::Str());
        seq_t int_seq = arg_seq(msg, symbol::Int());
        seq_t float_seq = arg_seq(msg, symbol::Float());
        seq_t escape_seq = arg_seq(msg, symbol::Esc());

        arg_tokens_.resize(count_bit1(all_seq));
        for(std::size_t i = 0; i < arg_tokens_.size(); i++)
        {
            arg_tokens_[i].type = arg_type_at_bit(i, str_seq, symbol::Str(), int_seq, 'd', float_seq, symbol::Float(), escape_seq, symbol::Esc());
            assert(arg_tokens_[i].type != symbol::Unknown() && "detected unknown symbol");
            arg_tokens_[i].pos = pos_of_nth_arg(msg, i);
        }
    }

    std::size_t count_args(char arg_symbol=symbol::Any()) const
    {
        if(arg_symbol == symbol::Any()) { return arg_tokens_.size(); }

        return std::count_if(
            arg_tokens_.begin(), 
            arg_tokens_.end(), 
            [arg_symbol](const ArgToken& arg){ return arg.type == arg_symbol; });
    };

    std::size_t next_nonescape_arg_i(std::size_t next_i = 0) const
    { 
        for(std::size_t i = next_i; i != arg_tokens_.size(); i++) 
        {
            if(arg_tokens_.at(i).type != symbol::Esc())
            {
                return i;
            }
        }
        throw std::invalid_argument("No more non escape arg.");
    }

    ArgToken operator[](std::size_t i) const
    {
        return arg_tokens_.at(i);
    }

    std::vector<ArgToken>::iterator begin() { return arg_tokens_.begin(); }
    std::vector<ArgToken>::iterator end() { return arg_tokens_.end(); }

    std::vector<ArgToken>::const_iterator begin() const { return arg_tokens_.begin(); }
    std::vector<ArgToken>::const_iterator end() const { return arg_tokens_.end(); }

    std::vector<ArgToken> arg_tokens() const { return arg_tokens_; }

private:
    cstr msg_;
    std::vector<ArgToken> arg_tokens_;
};


